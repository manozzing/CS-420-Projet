//#include "constants"
/*
 * Definitions
 */
#define NX 601
#define NY NX
#define BC_WIDTH 1
#define I1 BC_WIDTH
#define I2 I1+NX-1
#define J1 BC_WIDTH
#define J2 J1+NY-1
#define NXDIM NX+2*BC_WIDTH
#define NYDIM NY+2*BC_WIDTH
#define MAXSTEP 600

void advect1d(float s1d_out[], float s1d_in[], float u1d[], float dx, 
				float dt, int nx);
							
void advection(float s1[][NYDIM], float u[][NY], float v[][NY+1],
				float dt, float dx)
{
	float courant,sigma;
	float s1d_in[NXDIM], s1d_out[NXDIM], vel1d[NX+1];
	int i,j;

	// X advection
	for (j = J1; j <= J2; j++){
		for (i = 0; i < NXDIM; i++){
			s1d_in[i] = s1[i][j];
		}
		for(i = 0; i < NX+1; i++){
			vel1d[i]=u[i][j-J1];
		}
		advect1d(s1d_out,s1d_in,vel1d,dx,dt,NX);
		for(i = I1; i <= I2; i++){
			s1[i][j]=s1d_out[i];
		}
	}

	// Y advection
	for (i = I1; i <= I2; i ++){
		for(j = 0; j < NYDIM; j++){
			s1d_in[j]=s1[i][j];
		}
		for(j = 0; j < NY+1; j++){
			vel1d[j]=v[i-I1][j];
		}
		advect1d(s1d_out,s1d_in,vel1d,dx,dt,NY);
		for(j = J1; j <= J2; j++){
			s1[i][j]=s1d_out[j];
		}
	}
	return;
}
   
    
