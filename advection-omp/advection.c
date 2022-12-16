#include <stdio.h>
#include <omp.h>
#include "helpers.h"

void advect1d(int nx, int nxdim, int i1, int i2, float s1d_out[nx], 
				float s1d_in[nxdim], float vel1d[nx+1], float dx, float dt);
							
void advection(int nxdim, int nydim, int nx, int ny, float s1[nxdim][nydim], 
				float u[nx+1][ny], float v[nx][ny+1], float dt, float dx, 
				int i1, int i2, int j1, int j2)
{
	float courant,sigma;
	float s1d_in[nxdim], s1d_out[nxdim], vel1d[nx+1];
	int i,j;

	#pragma omp parallel
	{
	// X advection
	#pragma omp for schedule(static) private(i)
	for (j = j1; j <= j2; j++){
		for (i = 0; i <= nxdim; i++){
			s1d_in[i] = s1[i][j];
		}
		for(i = 0; i <= nx + 1; i++){
			vel1d[i] = u[i][j];
		}
		advect1d(nx,nxdim,i1,i2,s1d_out,s1d_in,vel1d,dx,dt);
		for(i = i1; i <= i2; i++){
			s1[i][j] = s1d_out[i];
		}
	}
	}

	#pragma omp barrier

	#pragma omp parallel
	{
		// Y advection
	#pragma omp for schedule(static) private(j)
	for (i = i1; i <= i2; i++){
		for(j = 0; j <= nydim; j++){
			s1d_in[j] = s1[i][j];
		}
		for(j = 0; j <= ny + 1; j++){
			vel1d[j] = v[i][j];
		}
		advect1d(ny,nydim,j1,j2,s1d_out,s1d_in,vel1d,dx,dt);
		for(j = j1; j <= j2; j++){
			s1[i][j] = s1d_out[j];
		}
	}
	}
	return;
}
   
    
