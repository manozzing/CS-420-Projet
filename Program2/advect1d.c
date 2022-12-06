/*
 * ======================= advection ===================
 * Integrate forward (advection only) by one time step.
 * Arguments:
 *
 *	s1	real array	values at current step
 *	s2	real array	values at next step
 *	c	real		flow speed in linear case
 *	dx	real		grid spacing
 *	dt	real		time step
 *	I1,I2	integers	indices bounding array data
 *	nx	integer		number of physical grid points
 *	advection_type
 *              char 		if 'L', linear advection;
 *				otherwise, nonlinear
 */

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

void advect1d(float s1d_out[], float s1d_in[], float vel1d[], float dx, 
				float dt, int nx)
{
	float courant;
	float sigma;
	for (int i = I1; i <= I2; i++) {
		courant= dt/dx * 0.5*(vel1d[i-I1]+vel1d[i+1-I1]);
		sigma=courant*courant/2;
		s1d_out[i] = s1d_in[i] - courant/2 * (s1d_in[i+1] - s1d_in[i-1])
		  + sigma * (s1d_in[i+1] - 2 * s1d_in[i] + s1d_in[i-1]);
	  }

	return;
}
