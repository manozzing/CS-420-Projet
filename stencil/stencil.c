/**
 * CS - 420 MP 3: Stencil 2D
 */
#include "stencil.h"
#include "mpi.h"
#include <stdio.h>

void send_ghosts(int tag, int w, int h, float src[w + 2][h + 2],
                 float rowBuf[w], float colBuf[h]) {
  // send to East
  if (kGridX < kGridCols-1) {
    copy_colbuf_out(w, h, src, w, colBuf);
    MPI_Send(colBuf, h, MPI_FLOAT, kRank+1, tag, MPI_COMM_WORLD);
  }
  // send to West
  if (kGridX > 0) {
    copy_colbuf_out(w, h, src, 1, colBuf);
    MPI_Send(colBuf, h, MPI_FLOAT, kRank-1, tag, MPI_COMM_WORLD);
  }
  // send to North
  if (kGridY > 0) {
    copy_rowbuf_out(w, h, src, 1, rowBuf);
    MPI_Send(rowBuf, w, MPI_FLOAT, kRank-kGridCols, tag, MPI_COMM_WORLD);
  }
  // send to South
  if (kGridY < kGridRows-1) {
    copy_rowbuf_out(w, h, src, h, rowBuf);
    MPI_Send(rowBuf, w, MPI_FLOAT, kRank+kGridCols, tag, MPI_COMM_WORLD);
  }
}

void recv_ghosts(int tag, int w, int h, float dst[w + 2][h + 2],
                 float rowBuf[w], float colBuf[h]) {
  // receive from West
  if (kGridX > 0) {
    MPI_Recv(colBuf, h, MPI_FLOAT, kRank-1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    copy_colbuf_in(w, h, dst, 0, colBuf);
  }
  // receive from East
  if (kGridX < kGridCols-1) {
    MPI_Recv(colBuf, h, MPI_FLOAT, kRank+1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    copy_colbuf_in(w, h, dst, w+1, colBuf);
  }
  // receive from South
  if (kGridY < kGridRows-1){
    MPI_Recv(rowBuf, w, MPI_FLOAT, kRank+kGridCols, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    copy_rowbuf_in(w, h, dst, h+1, rowBuf);
  }
  // receive from North
  if (kGridY > 0){
    MPI_Recv(rowBuf, w, MPI_FLOAT, kRank-kGridCols, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    copy_rowbuf_in(w, h, dst, 0, rowBuf);
  }
}

