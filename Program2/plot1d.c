/*
 * ========================= plot1d ====================
 * Plot1d plots a one-dimensional function using NCAR graphics
 * Arguments:
 *
 *	s	real array	array to plot (entire array passed here;
 *				  but only i1 ... i2 is plotted)
 *	i1,i2	integers	indices bounding (physical part of) array data
 *	nx	integer		size of array, not including ghost points
 *	n	integer		time step counter, from main program
 *	smax	real		max absolute value in s array - used in label
 *	overlay	integer		if nonzero, plot will be an overlay of two fields
 *	strue	real array	[optional] overlay field, ignored if overlay=0
 *	title	char string	title (time step, max info appended to this)
 *	name	char string	name to place on plot
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncarg/ncargC.h>
#include <ncarg/gks.h>
#define IWTYPE 1
#define WKID   1

void plot1d(float s[],int i1,int i2,int nx,int n,float smax,
	    int overlay,float strue[],char *title,char *name)
{
	int i,j;
	char label[200];
	float *both;

	sprintf(label,"%s  N=%d Max=%8.5f",title,n,smax);
	printf("Plotting \"%s\"\n",label);

/*
 * ... If overlay=0, simply plot s starting from i1;
 * ... if overlay=1, fill the both[] array with both fields, and plot that.
 */
	c_agseti("frame.",2);	/* suppress automatic graphics frame advance for now */

	if (overlay == 0) {

	  c_ezy(&s[i1],nx,label);

	} else {

	  both = (float *) malloc(2*nx*sizeof(float));
	  for (i=i1,j=0; i<=i2; i++,j++) {
	    both[j]    = s[i];
	    both[nx+j] = strue[i];
	  }
	  c_agsetr("DASH/SELECTOR.",2.0);
	  c_agseti("DASH/LENGTH.",20);
	  c_agsetc(c_agdshn(1),"$$$$$$$$$$$$$$$$$$$$");
	  c_agsetc(c_agdshn(2),"$$''$$''$$''$$''$$''");
	  c_ezmy(both,nx,2,nx,label);
	  free(both);
	}
/*
 * ... Add additional labels
 */
	c_set(.05,.95,.05,.95,0.,1.,0.,1.,1);
        c_pcmequ(0.02,1.0,name,0.01,90.,1.);
        c_pcmequ(1.0,0.05,"ATMS 502/CSE 566",0.01,0.,1.);
        c_pcmequ(0.0,0.05,"Spring 2022",0.01,0.,-1.);

/*
 * ... Done
 */
	c_frame();
	c_agseti("frame.",1);
	return;
}
