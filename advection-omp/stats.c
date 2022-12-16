#include <math.h>
#include <stdio.h>
// #include "helpers.h"

/*
 * ========================= stats =====================
 * Stats computes and prints out the max S values
 * Arguments:
 *
 *	s2	real array	Latest data. Check i1..i2;
 *				  [i1-1],[i2+1] = ghost zones
 *	i1,i2	integers	indices bounding array data
 *	nx	integer		size of data array without ghost zones
 *	n	integer		time step counter
 *	smax	real		holds max absolute value of s2
 */

void stats(int nxdim, int nydim, float s2[nxdim][nydim], 
			int i1, int i2, int j1, int j2, int nx, 
			int n, float dt, float *smax, float *smin)
{
	int i, j, imax, jmax, imin, jmin;
	float smax_tmp, smin_tmp, time;

	time = n * dt;
	smax_tmp = s2[i1][j1];
	smin_tmp = s2[i1][j1];
	imax = i1;
	imin = i1;
	jmax = j1;
	jmin = j1;
	for (i = i1 + 1; i <= i2; i++) {
		for (j = j1 + 1; j <= j2; j++) {
			if (s2[i][j] > smax_tmp) {
				smax_tmp = s2[i][j];
				imax = i;
				jmax = j;
			}
			if (s2[i][j] < smin_tmp) {
				smin_tmp = s2[i][j];
				imin = i;
				jmin = j;
			}
	  	}
	}

	printf("%5d %9.5f %9.5f %4d %4d %9.5f %4d %4d\n",n,time,
			smin_tmp,imin,jmin,smax_tmp,imax,jmax);
	*smax = smax_tmp;
	*smin = smin_tmp;

	return;
}

