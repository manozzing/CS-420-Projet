i/*
 * ======================= advection ===================
 * Integrate forward (advection only) by one time step.
 * Arguments:
 *
 *	s1	real array	values at current step
 *	s2	real array	values at next step
 *	c	real		flow speed in linear case
 



























*	dx	real		grid spacing
 *	dt	real		time step
 *	i1,i2	integers	indices bounding array data
 *	nx	integer		number of physical grid points
 *	advection_type
 *              char 		if 'L', linear advection;
 *				otherwise, nonlinear
 */
#include "constants"
void advect1d(float s1d_out[],float s1d_in[],float u1d[],float dx,float dt,
                   int i1,int i2,int nx,int advection_type)
{
	int i;
	float courant;
        float sigma;
	 if (advection_type == 1) {
	  for (i=i1; i<=i2; i++) {
               courant= dt/dx * 0.5*(u1d[i-i1]+u1d[i+1-i1])
               sigma=courant*courant/2;
               s1d_out[i] = s1d_in[i]-courant/2*(s1d_in[i+1]-s1d_in[i-1])+sigma*(s1d_in[i+1]-2*s1d_in[i]+s1d_in[i-1]);
	  }

	}else if (advection_type == 2) {
           for (i=i1; i<=i2; i++) {
               courant= dt/dx * 0.5*(u1d[i-i1]+u1d[i+1-i1])
               sigma=courant*courant/2;
                     if(courant>=0){
                        s1d_out[i] = s1d_in[i]-courant/2*(s1d_in[i+1]-s1d_in[i-1])+sigma*(s1d_in[i+1]-2*s1d_in[i]+s1d_in[i-1])-((1+courant)/6)*courant*(courant-1)*(s1d_in[i+1]-3s1d_in[i]+                        3s1d_in[i-1]-s1d_in[i-2]);}
	             else if (courant<0){
                        s1d_out[i] = s1d_in[i]-courant/2*(s1d_in[i+1]-s1d_in[i-1])+sigma*(s1d_in[i+1]-2*s1d_in[i]+s1d_in[i-1])-((1+abs(courant))/6)*courant*(courant+1)*(s1d_in[i-1]-3s1d_in[i]+3s1d_in[i+1]-s1d_in[i+2]);}}
         }else if (advection_type==3){
             for (i=i1; i<=i2; i++) {
                  courant= dt/dx * 0.5*(u1d[i-i1]+u1d[i+1-i1])
                  sigma=courant*courant/2;
                  s1d_out[i] = s1d_in[i]
                     + courant/60*(s1d_in[i-3]-9*s1d_in[i-2]+45*s1d_in[i-1]-45*s1d_in[i+1]+9*s1d_in[i+2]-s1d_in[i+3])
                     + (pow(courant,2))/360*(2*s1d_in[i-3]-27*s1d_in[i-2]+270*s1d_in[i-1]-490*s1d_in[i]+270*s1d_in[i+1]-27*s1d_in[i+2]+2*s1d_in[i+3])
                     + (pow(courant,3))/48*(-s1d_in[i-3]+8*s1d_in[i-2]-13*s1d_in[i-1]+13*s1d_in[i+1]-8*s1d_in[i+2]+s1d_in[i+3])
                     + (pow(courant,4))/144*(-s1d_in[i-3]+12*s1d_in[i-2]-39*s1d_in[i-1]+56*s1d_in[i]-39*s1d_in[i+1]+12*s1d_in[i+2]-s1d_in[i+3])
                     + (pow(courant,5))/240*(s1d_in[i-3]-4*s1d_in[i-2]+5*s1d_in[i-1]-5*s1d_in[i+1]+4*s1d_in[i+2]-s1d_i[i+3])
                     + (pow(courant,6))/720*(s1d_in[i-3]-6*s1d_in[i-2]+15*s1d_in[i-1]-20*s1d_in[i]+15*s1d_in[i+1]-6*s1d_in[i+2]+s1d_in[i+3])
            
 
	 }}

        else {
	  printf("Integrate: Error, unrecognized advection type '%c'\n",advection_type);
	  exit(1);
	}

	return;
}


