#include <math.h>
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

void stats(float s2[],int i1,int i2,int nx,int n,float *smax)
{
	int i;
	float stmp;

	stmp = fabs(s2[i1]);
	for (i=i1+1; i<=i2; i++) {
	  if (fabs(s2[i]) > stmp) stmp = fabs(s2[i]);
	}

	printf("Step %4d, Max = %9.5f\n",n,stmp);
	*smax = stmp;

	return;
}

