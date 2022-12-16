#ifndef HELPERS_H
#define HELPERS_H

#define BC_WIDTH 1
#define I1 kGridX * kGridWidth + (BC_WIDTH - 1)
#define I2 I1 + kGridWidth - (BC_WIDTH - 1)
#define J1 kGridY * kGridHeight + (BC_WIDTH - 1)
#define J2 J1 + kGridHeight - (BC_WIDTH - 1)
#define NXDIM NX + 2 * BC_WIDTH
#define NYDIM NY + 2 * BC_WIDTH
#define GRID_XDIM kGridWidth + 2 * BC_WIDTH
#define GRID_YDIM kGridHeight + 2 * BC_WIDTH
#define MAXSTEP 6000

extern int NX, NY, nstep;
extern int kRank, kNumPes, kNumIts;
extern int kGridRows, kGridCols;
extern int kGridX, kGridY;
extern int kGridWidth, kGridHeight;

// Swaps the values of a and b
// void swap(float **a, float **b);

// Copies a 2d stencil into a 1d buffer, discarding the padding
void copy_stencil_to_buffer(int w, int h, float in[w + 2][h + 2],
                            float out[w][h]);

// Copies a 1d buffer into a 2d stencil, at offset (x,y)
void copy_buffer_to_stencil(int w, int h, float dst[w + 2][h + 2], int ww, int hh,
                            float src[ww][hh], int x, int y);

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

// Sets up the enviroment, initializing the global variables
void setup_env(int argc, char *argv[]);

#endif //HELPERS_H

