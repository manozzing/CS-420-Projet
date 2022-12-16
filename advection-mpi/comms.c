#include "mpi.h"
#include <stdio.h>
#include "helpers.h"

void copy_rowbuf_out(int w, int h, float src[w + 2][h + 2], int y,
                     float rowBuf[w]);
void copy_colbuf_out(int w, int h, float src[w + 2][h + 2], int x,
					float colBuf[h]);
void copy_rowbuf_in(int w, int h, float dst[w + 2][h + 2], int y,
					float rowBuf[w]);
void copy_colbuf_in(int w, int h, float dst[w + 2][h + 2], int x,
					float colBuf[h]);

void send_ghosts(int tag, int w, int h, float src[w + 2][h + 2], float rowBuf[w], 
					float colBuf[h]) 
{
	// find neighbors
	int north_neighbor = kRank - kGridCols;
	int south_neighbor = kRank + kGridCols;
	int east_neighbor = kRank + 1;
	int west_neighbor = kRank - 1;

	if(kGridY > 0){ /* send north */
		copy_rowbuf_out(w, h, src, 1, rowBuf);
		MPI_Send(rowBuf, w, MPI_FLOAT, north_neighbor, tag, MPI_COMM_WORLD);
  	}
	if(kGridY < kGridRows - 1){ /* send south */
		copy_rowbuf_out(w, h, src, h, rowBuf);
		MPI_Send(rowBuf, w, MPI_FLOAT, south_neighbor, tag, MPI_COMM_WORLD);
  	} 
	if(kGridX < kGridCols - 1){ /* send east */
		copy_colbuf_out(w, h, src, w, colBuf);
		MPI_Send(colBuf, h, MPI_FLOAT, east_neighbor, tag, MPI_COMM_WORLD);
	}
	if(kGridX > 0){ /* send west */
		copy_colbuf_out(w, h, src, 1, colBuf);
		MPI_Send(colBuf, h, MPI_FLOAT, west_neighbor, tag, MPI_COMM_WORLD);
	}
}

void recv_ghosts(int tag, int w, int h, float dst[w + 2][h + 2], float rowBuf[w], 
					float colBuf[h]) 
{
	// find neighbors
	int north_neighbor = kRank - kGridCols;
	int south_neighbor = kRank + kGridCols;
	int east_neighbor = kRank + 1;
	int west_neighbor = kRank - 1;
	
	if(kGridY > 0){ /* receive north */
		MPI_Recv(rowBuf, w, MPI_FLOAT, north_neighbor, tag, MPI_COMM_WORLD,
						MPI_STATUS_IGNORE);
		copy_rowbuf_in(w, h, dst, 0, rowBuf);
	}
	if(kGridY < kGridRows - 1){ /* receive south */
		MPI_Recv(rowBuf, w, MPI_FLOAT, south_neighbor, tag, MPI_COMM_WORLD, 
						MPI_STATUS_IGNORE);
		copy_rowbuf_in(w, h, dst, h + 1, rowBuf);
	}
	if(kGridX < kGridCols - 1){ /* receive east */
		MPI_Recv(colBuf, h, MPI_FLOAT, east_neighbor, tag, MPI_COMM_WORLD,
						MPI_STATUS_IGNORE);
		copy_colbuf_in(w, h, dst, w + 1, colBuf);
	}
	if(kGridX > 0){ /* receive west */
		MPI_Recv(colBuf, h, MPI_FLOAT, west_neighbor, tag, MPI_COMM_WORLD,
						MPI_STATUS_IGNORE);
		copy_colbuf_in(w, h, dst, 0, colBuf);
	}
}
