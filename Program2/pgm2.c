/*
 *  ATMS 502 / CSE 566 -- Spring, 2022
 *  Demo for pgm2:  Linear and nonlinear advection
 *  ===>>>>>QURAT UL AIN FATIMA <<<=== and in "name" variable below <<<<<===
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncarg/ncargC.h>
#include <ncarg/gks.h>
#define IWTYPE 1
#define WKID   1

main()
{

/*
 * Definitions
 */
#include "constants"
char *name  = "QURAT UL AIN FATIMA";


/* Arrays and other variables */
        int colors,pltzero;
        char title[25];
        float cint,simtime,angh,angv;
        float splot[NX][NY],u[NX+1][NY],v[NX][NY+1];
	float s1[NXDIM][NYDIM],s2[NXDIM][NYDIM],strue[NXDIM];
	float strace[MAXSTEP],dt,courant,smax,c,dx,dy;
	int i,j,n,nstep,nplot;
	int  advection_type, reply[10];

/* Variables for run history */



/* Variables to reverse default black/white colors in NCAR Graphics */

	Gcolr_rep rgb1,rgb2;

/* Function prototype declarations
 * Prototypes declarations in C, like Interface blocks in Fortran, can
 * prevent difficult-to-track errors when functions are called incorrectly. 
 * More info:  https://computer.howstuffworks.com/c13.htm
 */
       void contr(int nx,int ny,float splot[NX][NY],float cint,float simtime,char *title,int colors,int pltzero,int nestX1,int nestX2,int nestY1,int nestY2,char *name);   
       void ic(float s1[NX][NY],float u[NX+1][NY],float v[NX][NY+1],float dx,float dy,int i1,int i2,int j1,int j2);
       void stats(float s[],int i1,int i2,int nx,int nstep,float *smax);
       void plot1d(float s[],int i1,int i2,int nx,int n,float smax,int overlay,float strue[],char *title,char *name);
    /*	void sfc(int nx,int maxstep,int nstep,float history[NX][MAXSTEP],
		 float simtime,float angh,float angv,char *title,char *name);*/
        void sfc(int nx,int ny,int nymax,float splot[NX][NY],float simtime,float angh,float angv,char *label,char *name);
	void bc(float s1[][NYDIM],int i1,int i2,int j1,int j2);
	void advection(float s1[][NYDIM],float u[][NY],float v[][NY+1],float dt,float dx,int advection_type);
 	/*void update(float s1[],float s2[],int i1,int i2,int nx);*/

/* Parameters and input .................................... */

	printf("Program #2       Numerical Fluid Dynamics\n\n");
	/*printf("NX=%d, BC_WIDTH=%d, I1=%d, I2=%d, NXDIM=%d\n",
		NX,BC_WIDTH,I1,I2,NXDIM);*/

	/*c = 1.0;*/

	dt = pi/400;
        dx=1/(NX-1);
        dy=1/(NY-1);

	/*printf("Enter courant number (normally <= 1; use 1.0 for nonlinear): ");
	scanf("%f",&courant);
	dt = courant*dx/c;*/


 	/*printf("For Courant number %5.2f, time step dt = %6.3f\n", courant, dt);
 	printf("Number of steps for one complete cycle = %.0f\n",( dx*(float)NX / c / dt ));*/

	printf("Enter number of time steps to take: ");
	scanf("%d",&nstep);
 	if (nstep > MAXSTEP) {
 	  printf("nstep too large: exceeds MAXSTEP, which equals %d\n",MAXSTEP);
 	  printf("increase MAXSTEP and recompile.\n");
 	  exit(1);
 	}

	printf("Enter plot interval, in steps (1=every step): ");
	scanf("%d",&nplot);

	printf("Enter 1 for lax, 2 for takacs, 3 for crowley 6th order: ");
	scanf("%d",&advection_type);

/*
 * Open the NCAR Graphics package and set colors.
 */
	gopen_gks("stdout",0);
	gopen_ws(WKID, NULL, IWTYPE);
	gactivate_ws(WKID);

	/* omit following four lines to invert black/white colors */
	rgb1.rgb.red = 1.; rgb1.rgb.green = 1.; rgb1.rgb.blue = 1.;
	rgb2.rgb.red = 0.; rgb2.rgb.green = 0.; rgb2.rgb.blue = 0.;
        gset_colr_rep(WKID,0,&rgb1);
        gset_colr_rep(WKID,1,&rgb2);
/*
 * X/Y-axis labels
 */
	c_anotat("X","S",0,0,0,0);
/*
 * Set default Y plot bounds
 */
	c_agsetf("Y/MINIMUM.",-1.2);
	c_agsetf("Y/MAXIMUM.", 1.2);
/*
 * Set and plot the initial condition
 */


	/*stats(s1,I1,I2,NX,0,&smax);*/
/*
  * Copy the initial condition to the "strue" array.
 *  We use it later since the initial condition is the true final solution.
 */    

        ic(s1,u,v,dx,dy,I1,I2,J1,J2);
       /* for (j=J1;j<=J2;j++){
	     for (i=I1; i<=I2; i++) {strue[i][j]=s1[i][j];}*/
/*
 * .. Integrate .....................................................
 */

	for (n=1; n<=nstep; n++) {

/*  . . . Set boundary conditions				*/
	   bc(s1,I1,I2,J1,J2);

/*  . . . Compute values at next step				*/
	   advection(s1,u,v,dt,dx,advection_type);

/*  . . . Do array update at end of time step			*/
 	 /* update(s1,s2,I1,I2,NX);*/

/*  . . . Copy latest solution s2() to history array
 *        "i" used for "s2" array subscripting			*/

/*  . . . Stats							*/
	  /*stats(s2,I1,I2,NX,n,&smax);*/
	 /* strace[n-1] = smax;*/
          printf("Plotting contours.\n");
          for (j=J1; j<=J2; j++){
              for (i=I1;i<=I2;i++){
                 splot[i-I1][j-J1]=s1[i][j];}}
          
           cint =1;
           colors=0;
           pltzero=-1;
           simtime = dt*(float)n;
           sprintf(title,"Contour plot at n = %d",n);
	   contr(NX,NY,splot,cint,simtime,title,colors,pltzero,0,0,0,0,name);
          printf("Plotting surface.\n");
          for (j=J1; j<=J2; j++){
              for (i=I1;i<=I2;i++){
                 splot[i-I1][j-J1]=s1[i][j];}}
          angh =-45.0;
          angv = 20.0;
          sprintf(title,"Surface plot at n = %d",n);
	  sfc(NX,NY,NY,splot,simtime,angh,angv,title,name);
/*  . . . Plot fields when needed				*/
	  /*if (n == nstep || n%nplot == 0) {
	    if (advection_type == 'L') {
	      plot1d(s2,I1,I2,NX,n,smax,1,strue,title,name);
	    } else {
	      plot1d(s2,I1,I2,NX,n,smax,0,strue,title,name);
	    }*/
	  

/*  . . . Check if problem out of bounds			*/
	  /*if (smax > 1.5) {
	    printf("Stop - solution blowing up at step %d\n",n);
	    plot1d(s2,I1,I2,NX,n,smax,0,strue,"Solution blowing up",name);
	    nstep = n;
	    break;
	  }*/

	}	/* end of time loop n = 1,...,nstep */

/*
 * Run complete - do final plots
 */

/* . . Plot Smax(t)						*/
	c_agsetf("Y/MINIMUM.",0.0);
	c_agsetf("Y/MAXIMUM.",1.5);
	c_anotat("N","Max value",0,0,0,0);
	/*stats(strace,0,nstep-1,nstep,nstep,&smax);*/

/* . . Plot history surface s(x,t)
 *     Three different viewpoints are used */
	/*sfc(NX,MAXSTEP,nstep,history,(dt*(float)nstep),-90., 0.,
          "Time-Space evolution (view: -90,  0)",name);
	sfc(NX,MAXSTEP,nstep,history,(dt*(float)nstep),-75., 5.,
	  "Time-Space evolution (view: -75, +5)",name);
	sfc(NX,MAXSTEP,nstep,history,(dt*(float)nstep),-30.,20.,
	  "Time-Space evolution (view: -30,+20)",name);*/

/*
 *  Close the graphics package and stop.
 */

	gdeactivate_ws(WKID);
	gclose_ws(WKID);
	gclose_gks();

	exit;
}
