/*
 * ============================ bc =====================
 * BC sets the boundary conditions
 * Arguments:
 *
 *	s1	real array	values at current time step
 *	i1,i2	integers	indices bounding array data
 *	nx	integer		main array size, not including
 *	ny      			extra 'ghost' zones/points
 */

#include <stdio.h>
// #include "helpers.h"

void bc(int nxdim, int nydim, float s1[nxdim][nydim], 
		int i1, int i2, int j1, int j2)
{
	for (int i = i1; i <= i2; i++){
		s1[i][j1-1]=s1[i][j1];
		s1[i][j1-2]=s1[i][j1];
		s1[i][j1-3]=s1[i][j1];
		s1[i][j2+1]=s1[i][j2];
		s1[i][j2+2]=s1[i][j2];
		s1[i][j2+3]=s1[i][j2];
	}
	for (int j = j1; j <= j2; j++){
		s1[i1-1][j]=s1[i1][j];
		s1[i1-2][j]=s1[i1][j];
		s1[i1-3][j]=s1[i1][j];
		s1[i2+1][j]=s1[i2][j];
		s1[i2+2][j]=s1[i2][j];
		s1[i2+3][j]=s1[i2][j];  
	}
	return;
}

