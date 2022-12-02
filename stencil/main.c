#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <mpi.h>
#include <sys/time.h>

#include "stencil.h"
#include "utils.h"

#ifndef VERBOSE_LEVEL
#define VERBOSE_LEVEL 1
#endif

int main(int argc, char *argv[]) {
  // Setup the environment
  setup_env(argc, argv);
  #if VERBOSE_LEVEL >= 1
    // Print the grid information from PE0
    if (kRank == 0) {
      printf("[%d] there are %d pes, divided into a %d x %d grid.\n", kRank,
            kNumPes, kGridRows, kGridCols);
    }
  #endif
  #if VERBOSE_LEVEL >= 2
    printf("[%d] corresponds to coordinate (%d,%d).\n", kRank, kGridX, kGridY);
  #endif
  // Compute the size of our local stencil
  int w = kWidth / kGridCols;
  int h = kHeight / kGridRows;
  assert(((w * kGridCols) == kWidth) && ((h * kGridRows) == kHeight));
  #if VERBOSE_LEVEL >= 2
    // Print the tile size from PE0
    if (kRank == 0) {
      printf("[%d] each PE is taking a %d by %d tile.\n", kRank, h, w);
    }
  #endif
  // Allocate all of the necessary buffers
  float *in = (float *)malloc(sizeof(float) * (w + 2) * (h + 2));
  float *out = (float *)malloc(sizeof(float) * (w + 2) * (h + 2));
  float *rowBuf = (float *)malloc(sizeof(float) * w);
  float *colBuf = (float *)malloc(sizeof(float) * h);
  // Initialize the stencils
  init_stencil(kGridX * w, kGridY * h, w, h, (float(*)[w + 2])in);
  memcpy(out, in, sizeof(float) * (w + 2) * (h + 2));
  double start, end;
  start = get_wall_time();
  // Iterate for the number of iterations
  int it;
  for (it = 0; it < kNumIts; it++) {
    // Send our ghost cells to the other PEs
    send_ghosts(it, w, h, (float(*)[w + 2])in, rowBuf, colBuf);
    // Receive ghost cells from the other PEs
    recv_ghosts(it, w, h, (float(*)[w + 2])in, rowBuf, colBuf);
    // Perform our local stencil computation
    stencil_2d(w, h, (float(*)[w + 2])in, (float(*)[w + 2])out);
    // Swap the in and out buffers for the next iteration
    swap(&in, &out);
  }
  // Wait for all of the threads to finish communicating
  MPI_Barrier(MPI_COMM_WORLD);
  end = get_wall_time();
  if (kRank == 0) {
    // Print the runtime from PE0
    printf("[%d] It took %.3lf seconds to run %d iterations.\n",
           kRank, end - start, kNumIts);
  }
  // Collect the results at the root
  if (kRank == 0) {
    float *all = (float *)malloc(sizeof(float) * kWidth * kHeight);
    float *recv = (float *)malloc(sizeof(float) * w * h);
    for (it = 0; it < kNumPes; it++) {
      int x = (it % kGridCols) * w;
      int y = (it / kGridCols) * h;
      #if VERBOSE_LEVEL >= 2
            printf("[%d] Receiving values from %d into (%d, %d).\n", kRank, it, x, y);
      #endif
      // No receive needed for PE0 since the tile is local
      if (it == 0) {
        copy_stencil_to_buffer(w, h, (float(*)[w + 2])in, (float(*)[w])recv);
      } else {
        MPI_Recv(recv, w * h, MPI_FLOAT, it, it, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
      }
      copy_buffer_to_stencil(kWidth, kHeight, (float(*)[kWidth])all, w, h,
                             (float(*)[w])recv, x, y);
    }
  #if VERBOSE_LEVEL >= 1
      printf("[%d] Final results:\n", kRank);
      print_matrix(kWidth, kHeight, (float(*)[kWidth])all);
  #endif
    free(all);
    free(recv);
  } else {
    float *send = (float *)malloc(sizeof(float) * w * h);
    copy_stencil_to_buffer(w, h, (float(*)[w + 2])in, (float(*)[w])send);
    MPI_Send(send, w * h, MPI_FLOAT, 0, kRank, MPI_COMM_WORLD);
    free(send);
  }
  // free the various buffers
  free(in);
  free(out);
  free(rowBuf);
  free(colBuf);
  // terminate normally
  MPI_Finalize();
  return 0;
}
