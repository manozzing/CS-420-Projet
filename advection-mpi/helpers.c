#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

#include "helpers.h"

int NX, NY, nstep;
int kRank, kNumPes, kNumIts;
int kGridRows, kGridCols;
int kGridX, kGridY;
int kGridWidth, kGridHeight;

// void swap(float **a, float **b) {
//   float *tmp = *a;
//   *a = *b;
//   *b = tmp;
// }

// A function to find largest prime factor
// Adapted from: https://www.geeksforgeeks.org/find-largest-prime-factor-number/
int max_prime_factor(int n) {
  if (n == 1)
    return 1;
  int maxPrime = -1;
  while (n % 2 == 0) {
    maxPrime = 2;
    n >>= 1;
  }
  int i;
  for (i = 3; i <= sqrt(n); i += 2) {
    while (n % i == 0) {
      maxPrime = i;
      n = n / i;
    }
  }
  if (n > 2)
    maxPrime = n;
  return maxPrime;
}

void copy_stencil_to_buffer(int w, int h, float in[w + 2][h + 2],
                            float out[w][h]) {
  for (int i = 0; i < w; i++) {
    memcpy(&out[i][0], &in[i + 1][1], sizeof(float) * h);
  }
}

void copy_buffer_to_stencil(int w, int h, float dst[w + 2][h + 2], int ww, int hh,
                            float src[ww][hh], int x, int y) {
  for (int i = 0; i < ww; i++) {
    memcpy(&dst[(x + 1) + i][y + 1], &src[i][0], sizeof(float) * hh);
  }
}

void copy_rowbuf_out(int w, int h, float src[w + 2][h + 2], int y,
                     float rowBuf[w]) {
  for (int i = 1; i <= w; i++) {
    rowBuf[i - 1] = src[i][y];
  }
}

void copy_colbuf_out(int w, int h, float src[w + 2][h + 2], int x,
                     float colBuf[h]) {
  memcpy(colBuf, &src[x][1], sizeof(float) * h);
}

void copy_rowbuf_in(int w, int h, float dst[w + 2][h + 2], int y,
                    float rowBuf[w]) {
  int i;
  for (i = 1; i <= w; i++) {
    dst[i][y] = rowBuf[i - 1];
  }
}

void copy_colbuf_in(int w, int h, float dst[w + 2][h + 2], int x,
                    float colBuf[h]) {
  memcpy(&dst[x][1], colBuf, sizeof(float) * h);
}

void setup_env(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &kNumPes);
    MPI_Comm_rank(MPI_COMM_WORLD, &kRank);
    if (argc != 4) {
      if (kRank == 0) {
        fprintf(stderr, "usage is: %s <nx> <ny> <nstep>\n", argv[0]);
      }
      exit(1);
    }
    // Parse the arguments
    NX = atoi(argv[1]);
    NY = atoi(argv[2]);
    nstep = atoi(argv[3]);
    assert((NX > 0) && (NY > 0) && (kNumIts >= 0));
  /* Estimate communications grid */
    kGridCols = max_prime_factor(kNumPes);
    kGridRows = kNumPes / kGridCols;
    assert((kGridRows * kGridCols) == kNumPes);
  /* Find the cooridnates within the grid */
    kGridX = kRank % kGridCols;
    kGridY = kRank / kGridCols;
  /* Compute the size of local grid */
    kGridWidth = NX / kGridCols;
    kGridHeight = NY / kGridRows;
    assert(((kGridWidth * kGridCols) == NX) && ((kGridHeight * kGridRows) == NY));
}

