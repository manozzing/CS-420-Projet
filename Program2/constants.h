#ifndef CONSTANTS_H

#define NX 121
#define NY NX
#define BC_WIDTH 2
#define I1 BC_WIDTH - 1
#define I2 I1 + NX - BC_WIDTH - 1
#define J1 BC_WIDTH - 1
#define J2 J1 + NY - BC_WIDTH - 1
#define NXDIM NX + 2 * BC_WIDTH
#define NYDIM NY + 2 * BC_WIDTH
#define MAXSTEP 600

#endif //CONSTANTS_H
