#ifndef MP3_UTILS_H
#define MP3_UTILS_H

double get_wall_time();

// Prints a matrix to stdout
void print_matrix(int m, int n, float a[m][n]);

// Swaps the values of a and b
void swap(float **a, float **b);

// Finds the largest prime factor of an integer
int max_prime_factor(int n);

// Row and column buffer helper functions. Copies a value into/out of the PE's
// tile from a buffer, with an x/y offset
void copy_rowbuf_out(int w, int h, float src[w + 2][h + 2], int y,
                     float rowBuf[w]);
void copy_colbuf_out(int w, int h, float src[w + 2][h + 2], int x,
                     float colBuf[h]);
void copy_rowbuf_in(int w, int h, float dst[w + 2][h + 2], int y,
                    float rowBuf[w]);
void copy_colbuf_in(int w, int h, float dst[w + 2][h + 2], int x,
                    float colBuf[h]);

#endif //MP3_UTILS_H
