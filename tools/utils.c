#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>

#include "utils.h"

double get_wall_time() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec + (tp.tv_usec / 1e6);
}

void print_matrix(int m, int n, float a[m][n]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%.3f\t", a[j][i]);
    }
    printf("\n");
  }
}

void swap(float **a, float **b) {
  float *tmp = *a;
  *a = *b;
  *b = tmp;
}

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

void copy_rowbuf_out(int w, int h, float src[w + 2][h + 2], int y,
                     float rowBuf[w]) {
  int i;
  for (i = 1; i <= w; i++) {
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
