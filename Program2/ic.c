/*
 * ============================ ic =====================
 * IC sets the initial condition
 * Arguments:
 *
 *	s1	real array	IC data. Set i1..i2 here;
 *				  [i1-1],[i2+1] = ghost zones
 *				  if 1 ghost point on each side
 *	dx	real		grid spacing
 *	i1,i2	integers	indices bounding array data
 *	nx	integer		number of physical grid points
 *
 */
#include <math.h>
#include "constants"
void ic(float s1[NX][NY],float u[NX+1][NY],float v[NX][NY+1],float dx,float dy,int i1,int i2,int j1,int j2)
{
	int i,j;
	float x,y,d;
        float x0=0.0;
        float y0=0.30;
        float r=0.125;       
	float pi = 4.0*atan(1.0);
 	/*length = dx * (float) nx;

         * In loop below:
 	 * i runs i1...i2 and is actual array offset/memory adddress
 	 * i=i1 is the first physical point; i-i1 used to find X value
 	 */

	for (i=i1; i<=i2; i++) {
             for (j=j1; j<=j2; j++){
                  x = -0.5 + dx * (i-i1);
                  y= -0.5 + dy*(j-j1);
                  d= sqrt(pow((x-x0),2)+pow((y-y0),2));
                     if( d > r)
                         s1[i][j] = 0;
                      else
                 s1[i][j]=5*(1+cos(pi*d/r));

}
}
        for (j=j1;j<=j2;j++){
            for (i=i1;i<=i2+1;i++){
                x = -0.5 + dx * (i-i1)-dx/2;
                y = -0.5 + dy*(j-j1);	
                u[i][j]=-2*y;}
}
        
        for (i=i1;i<=i2;i++){
            for (j=j1;j<=j2+1;j++){
                x = -0.5 + dx *(i-i1);
                y = -0.5 + dy*(j-j1)-dy/2;      
                v[i][j]=-2*y;}}
	return;
}


