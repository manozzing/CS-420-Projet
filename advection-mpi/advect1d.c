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

#include <stdio.h>
// #include "helpers.h"

void advect1d(int nx, int nxdim, int i1, int i2, float s1d_out[nx], 
				float s1d_in[nxdim], float vel1d[nx+1], float dx, float dt)
{
	float courant;
	float sigma;
	for (int i = i1; i <= i2; i++) {
		courant= dt/dx * 0.5*(vel1d[i]+vel1d[i+1]);
		sigma=courant*courant/2;
    	s1d_out[i] = s1d_in[i] - courant/2 * (s1d_in[i+1] - 
				s1d_in[i-1]) + sigma * (s1d_in[i+1] - 
				2 * s1d_in[i] + s1d_in[i-1]);
	  }

	return;
}
