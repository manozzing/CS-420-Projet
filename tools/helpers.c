#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <assert.h>

#include "helpers.h"
#include "utils.h"

#define SCALING_FACTOR 0.125f

int kRank, kNumPes, kNumIts;
int kGridRows, kGridCols;
int kGridX, kGridY;
int kWidth, kHeight;

void init_stencil(int xOff, int yOff, int m, int n, float a[m + 2][n + 2]) {
  int i, j;
  for (i = 0; i <= (m + 1); i++) {
    for (j = 0; j <= (n + 1); j++) {
      if (i == 0 || j == 0 || i == (m + 1) || j == (n + 1)) {
        a[i][j] = 0.0f;
      } else {
        a[i][j] = SCALING_FACTOR * ((i + xOff) * (j + yOff));
      }
    }
  }
}

void stencil_2d(int w, int h, float in[w + 2][h + 2], float out[w + 2][h + 2]) {
  int i, j;
  for (i = 1; i <= w; i++) {
    for (j = 1; j <= h; j++) {
      out[i][j] =
          in[i + 1][j] + in[i - 1][j] + in[i][j] + in[i][j - 1] + in[i][j + 1];
    }
  }
}

void copy_stencil_to_buffer(int w, int h, float in[w + 2][h + 2],
                            float out[w][h]) {
  int i;
  for (i = 0; i < w; i++) {
    memcpy(&out[i][0], &in[i + 1][1], sizeof(float) * h);
  }
}

void copy_buffer_to_stencil(int w, int h, float dst[w][h], int ww, int hh,
                            float src[ww][hh], int x, int y) {
  int i;
  for (i = 0; i < ww; i++) {
    memcpy(&dst[x + i][y], &src[i][0], sizeof(float) * hh);
  }
}

void setup_env(int argc, char *argv[]) {
  // Initialize the MPI environment
  MPI_Init(&argc, &argv);
  // Get the rank of the process
  MPI_Comm_rank(MPI_COMM_WORLD, &kRank);
  // Get the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &kNumPes);
  // Error if unexpected number of args
  if (argc != 4) {
    if (kRank == 0) {
      fprintf(stderr, "usage is: %s <width> <height> <numIts>\n", argv[0]);
    }
    exit(1);
  }
  // Parse the arguments
  kHeight = atoi(argv[1]);
  kWidth = atoi(argv[2]);
  kNumIts = atoi(argv[3]);
  assert((kWidth > 0) && (kHeight > 0) && (kNumIts >= 0));
  // Establish the communications grid
  kGridCols = max_prime_factor(kNumPes);
  kGridRows = kNumPes / kGridCols;
  assert((kGridRows * kGridCols) == kNumPes);
  // Find our coordinates within the grid
  kGridX = kRank % kGridCols;
  kGridY = kRank / kGridCols;
}