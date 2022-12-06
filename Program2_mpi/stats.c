#include <math.h>
#include <stdio.h>
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

void stats(float s2[NXDIM][NYDIM], int i1, int i2, int j1, int j2, int nx, 
			int n, float *smax, float *smin)
{
	int i, j;
	float smax_tmp, smin_tmp;

	smax_tmp = fabs(s2[i1][j1]);
	smin_tmp = fabs(s2[i1][j1]);
	for (i = i1 + 1; i <= i2; i++) {
		for (j = j1 + 1; j <= j2; j++) {
	  		if (fabs(s2[i][j]) > smax_tmp) smax_tmp = fabs(s2[i][j]);
			if (fabs(s2[i][j]) < smin_tmp) smin_tmp = fabs(s2[i][j]);
	  	}
	}

	printf("Step %4d, Max = %9.5f, Min = %9.5f\n",n,smax_tmp,smin_tmp);
	*smax = smax_tmp;
	*smin = smin_tmp;

	return;
}

