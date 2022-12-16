#ifndef HELPERS_H
#define HELPERS_H

// #define NX 120
// #define NY NX
#define BC_WIDTH 2
#define I1 BC_WIDTH - 1
#define I2 I1 + NX - (BC_WIDTH - 1)
#define J1 BC_WIDTH - 1
#define J2 J1 + NY - (BC_WIDTH - 1)
#define NXDIM NX + 2 * BC_WIDTH
#define NYDIM NY + 2 * BC_WIDTH
#define MAXSTEP 6000

extern int NX, NY, nstep;
// extern int I1, I2, J1, J2;
// extern int NXDIM, NYDIM;

// Sets up the enviroment, initializing the global variables
void setup_env(int argc, char *argv[]);

#endif //HELPERS_H

