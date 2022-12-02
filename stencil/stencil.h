#ifndef STENCIL2D_H
#define STENCIL2D_H

/**
 * CS - 420 MP 3: Stencil 2D
 */
#include "utils.h"
#include "helpers.h"

// Sends the ghost values with a tag, using row/colBuf for temporary storage
void send_ghosts(int tag, int w, int h, float src[w + 2][h + 2],
                 float rowBuf[w], float colBuf[h]);

// Receives the ghost values with a tag, using row/colBuf for temporary storage
void recv_ghosts(int tag, int w, int h, float dst[w + 2][h + 2],
                 float rowBuf[w], float colBuf[h]);

#endif //STENCIL2D_H
