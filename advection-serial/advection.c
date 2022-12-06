//#include "constants"
#include <stdio.h>
#include "constants.h"

void advect1d(float s1d_out[NX], float s1d_in[NXDIM], float vel1d[NX+1], float dx, 
				float dt, int nx);
							
void advection(float s1[NXDIM][NYDIM], float u[NX+1][NY], float v[NX][NY+1],
				float dt, float dx)
{
	float courant,sigma;
	float s1d_in[NXDIM], s1d_out[NXDIM], vel1d[NX+1];
	int i,j;

	// X advection
	for (j = J1; j <= J2; j++){
		for (i = 0; i <= NXDIM; i++){
			s1d_in[i] = s1[i][j];
		}
		for(i = 0; i <= NX + 1; i++){
			vel1d[i] = u[i][j];
		}
		advect1d(s1d_out,s1d_in,vel1d,dx,dt,NX);
		for(i = I1; i <= I2; i++){
			s1[i][j] = s1d_out[i];
		}
	}

	// Y advection
	for (i = I1; i <= I2; i++){
		for(j = 0; j <= NYDIM; j++){
			s1d_in[j] = s1[i][j];
		}
		for(j = 0; j <= NY + 1; j++){
			vel1d[j] = v[i][j];
		}
		advect1d(s1d_out,s1d_in,vel1d,dx,dt,NY);
		for(j = J1; j <= J2; j++){
			s1[i][j] = s1d_out[j];
		}
	}
	return;
}
   
    
