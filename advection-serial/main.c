/*
 *  Linear and nonlinear advection
 *  ===>>>>> Manho Park, Yicen Liu <<<===
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include "helpers.h"
// #include <ncarg/ncargC.h>
// // #include <ncarg/gks.h>
// #define IWTYPE 1
// #define WKID   1

double get_wall_time() {
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return tp.tv_sec + (tp.tv_usec / 1e6);
}

int main(int argc, char *argv[])
{

/* Set up the environment */
	setup_env(argc, argv);
	char *name  = "Manho Park, Yicen Liu";

/* Arrays and other variables */
	int colors,pltzero;
	char title[25];
	float pi,cint,simtime,angh,angv;
	float splot[NX][NY],u[NX+1][NY],v[NX][NY+1];
	float s1[NXDIM][NYDIM],s2[NXDIM][NYDIM],strue[NXDIM];
	float strace[MAXSTEP],dt,courant,smax,smin,c,dx,dy;
	int i,j,n,nplot;
	int reply[10];
	double start, end;

/* Variables for run history */

/* Variables to reverse default black/white colors in NCAR Graphics */

	// Gcolr_rep rgb1,rgb2;

/* Function prototype declarations
 * Prototypes declarations in C, like Interface blocks in Fortran, can
 * prevent difficult-to-track errors when functions are called incorrectly. 
 * More info:  https://computer.howstuffworks.com/c13.htm
 */
	// void contr(int nx, int ny, float splot[NX][NY], float cint, float simtime,
	// 			char *title, int colors, int pltzero, int nestX1, int nestX2,
	// 			int nestY1, int nestY2, char *name);   
	void ic(int nxdim, int nydim, int nx, int ny, float s1[nxdim][nydim], 
        float u[nx + 1][ny], float v[nx][ny + 1], float dx, float dy, 
		int i1, int i2, int j1, int j2);
	void bc(int nxdim, int nydim, float s1[nxdim][nydim], 
		int i1, int i2, int j1, int j2);
	void stats(int nxdim, int nydim, float s2[nxdim][nydim], 
			int i1, int i2, int j1, int j2, int nx, 
			int n, float dt, float *smax, float *smin);
    // void sfc(int nx, int ny, int nymax, float splot[NX][NY], float simtime,
	// 		float angh, float angv, char *label, char *name);
	void advection(int nxdim, int nydim, int nx, int ny, float s1[nxdim][nydim], 
				float u[nx+1][ny], float v[nx][ny+1], float dt, float dx, 
				int i1, int i2, int j1, int j2);

/* Parameters and input .................................... */

	/*printf("NX=%d, BC_WIDTH=%d, I1=%d, I2=%d, NXDIM=%d\n",
		NX,BC_WIDTH,I1,I2,NXDIM);*/

	printf("Numerical Fluid Dynamics\n\n");

	/*c = 1.0;*/
	pi = 4.0*atan(1.0);
	dt = pi/nstep;
	dx=1.0/(NX-1);
	dy=1.0/(NY-1);

	/*printf("Enter courant number (normally <= 1; use 1.0 for nonlinear): ");
	scanf("%f",&courant);
	dt = courant*dx/c;*/


 	/*printf("For Courant number %5.2f, time step dt = %6.3f\n", courant, dt);
 	printf("Number of steps for one complete cycle = %.0f\n",( dx*(float)NX / c / dt ));*/

	printf("NX = %4d, NY = %4d, dx = %9.5f, dy = %9.5f\n", NX, NY, dx, dy);

	// printf("Enter plot interval, in steps (1=every step): ");
	// scanf("%d",&nplot);

/*
 * Open the NCAR Graphics package and set colors.
 */
	// en_gks("stdout",0);
	// gopen_ws(WKID, NULL, IWTYPE);
	// gactivate_ws(WKID);gop

	/* omit following four lines to invert black/white colors */
	// rgb1.rgb.red = 1.; rgb1.rgb.green = 1.; rgb1.rgb.blue = 1.;
	// rgb2.rgb.red = 0.; rgb2.rgb.green = 0.; rgb2.rgb.blue = 0.;
	// gset_colr_rep(WKID,0,&rgb1);
	// gset_colr_rep(WKID,1,&rgb2);
/*
 * X/Y-axis labels
 */
	// c_anotat("X","S",0,0,0,0);
/*
 * Set default Y plot bounds
 */
	// c_agsetf("Y/MINIMUM.",-1.2);
	// c_agsetf("Y/MAXIMUM.", 1.2);
/*
 * Set and plot the initial condition
 */

/*
  * Copy the initial condition to the "strue" array.
 *  We use it later since the initial condition is the true final solution.
 */    

	ic(NXDIM,NYDIM,NX,NY,s1,u,v,dx,dy,I1,I2,J1,J2);
	start = get_wall_time(); // Record time right after initial condition
	printf("Initial condition:\n");
	printf("%5s %9s %9s %4s %4s %9s %4s %4s\n","Step","Time",
			"Max","at I","J","Min","at I","J");
	stats(NXDIM,NYDIM,s1,I1,I2,J1,J2,NX,0,dt,&smax,&smin);
	/* for (j=J1;j<=J2;j++){
		for (i=I1; i<=I2; i++) {strue[i][j]=s1[i][j];}*/
/*
/*  . . . Plot initial conditions				*/
	// cint = 0.5;
	// colors = 0;
	// pltzero = -1;
	// simtime = dt*(float)n;
	// for (j = J1; j <= J2; j++){
	//     for (i = I1; i <= I2; i++){
	// 		splot[i-I1][j-J1] = s1[i][j];
	// 	}
	// }
	// contr(NX,NY,splot,cint,simtime,title,colors,pltzero,0,0,0,0,name);
	// for (j = J1; j <= J2; j++){
	//     for (i = 0; i <= NX + 1; i++){
	// 		splot[i-I1][j-J1] = 0.5 * (u[i][j-J1] + u[i+1][j-J1]);
	// 	}
	// }
	// contr(NX,NY,splot,cint,simtime,title,colors,pltzero,0,0,0,0,name);
	// for (j = 0; j <= NY + 1; j++){
	// 	for (i = I1; i <= I2; i++){
	// 		splot[i-I1][j-J1] = 0.5 * (v[i-I1][j] + v[i-I1][j+1]);
	// 	}
	// }
	// contr(NX,NY,splot,cint,simtime,title,colors,pltzero,0,0,0,0,name);
	// printf("Using IC settings for u,v");

/* .. Integrate ...............................................*/

	for (n = 1; n <= nstep; n++) {

/*  . . . Set boundary conditions				*/
		bc(NXDIM,NYDIM,s1,I1,I2,J1,J2);

/*  . . . Compute values at next step				*/
		advection(NXDIM,NYDIM,NX,NY,s1,u,v,dt,dx,I1,I2,J1,J2);

/*  . . . Do array update at end of time step			*/
 	 /* update(s1,s2,I1,I2,NX);*/

/*  . . . Copy latest solution s2() to history array
 *        "i" used for "s2" array subscripting			*/

	 /* strace[n-1] = smax;*/
/*  . . . Plot contours							*/
	   	// printf("Plotting contours.\n");
	   	// for (j = J1; j <= J2; j++){
	    //  	for (i = I1; i <= I2; i++){
		// 		splot[i-I1][j-J1] = s1[i][j];
		// 	}
		// }
		// sprintf(title,"Contour plot at n = %d",n);
		// if (n == nstep || n%nplot == 0) {
	    //   	contr(NX,NY,splot,cint,simtime,title,colors,pltzero,0,0,0,0,name);
		// }
/*  . . . Plot surface				*/
        // printf("Plotting surface.\n");
        // for (j = J1; j <= J2; j++){
        //     for (i = I1;i <= I2; i++){
        //     	splot[i-I1][j-J1] = s1[i][j];
		// 	}
		// }
		// angh = -75.0;
		// angv = 20.0;
		// sprintf(title,"Surface plot at n = %d",n);
		// if (n == nstep || n%nplot == 0) {
	    //   	sfc(NX,NY,NY,splot,simtime,angh,angv,title,name);
		// }  

/*  . . . Check if problem out of bounds			*/
	  /*if (smax > 1.5) {
	    printf("Stop - solution blowing up at step %d\n",n);
	    nstep = n;
	    break;
	  }*/

	}	/* end of time loop n = 1,...,nstep */
	end = get_wall_time(); // Get time after finishing for loop

	printf("Final results:\n");
	printf("%5s %9s %9s %4s %4s %9s %4s %4s\n","Step","Time",
				"Max","at I","J","Min","at I","J");
	stats(NXDIM,NYDIM,s1,I1,I2,J1,J2,NX,nstep,dt,&smax,&smin);
	printf("It took %.6lf seconds.\n", end - start);
/*
 * Run complete - do final plots
 */

/* . . Plot Smax(t)						*/
	// c_agsetf("Y/MINIMUM.",0.0);
	// c_agsetf("Y/MAXIMUM.",1.5);
	// c_anotat("N","Max value",0,0,0,0);
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

	// gdeactivate_ws(WKID);
	// gclose_ws(WKID);
	// gclose_gks();
	exit(0);
}
