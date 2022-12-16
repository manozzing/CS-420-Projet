/*
 *  Linear and nonlinear advection
 *  ===>>>>> Manho Park, Yicen Liu <<<===
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <assert.h>
#include <sys/time.h>
#include <string.h>

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
	
/* Setup environment */
	setup_env(argc,argv);
	char *name  = "Manho Park, Yicen Liu";

/* Arrays and other variables */
	int colors,pltzero;
	char title[25];
	float pi,cint,simtime,angh,angv;
	// float splot[NX][NY];
	float u[kGridWidth+1][kGridHeight],v[kGridWidth][kGridHeight+1];
	// float s1[NXDIM][NYDIM],s2[NXDIM][NYDIM],strue[NXDIM];
	float strace[MAXSTEP],dt,courant,smax,smin,c,dx,dy;
	int i,j,n,nplot;
	int reply[10];
	double start, end;
	/* Allocate all of the necessary buffers */
	float rowBuf[kGridWidth];
	float colBuf[kGridHeight];
	float in[kGridWidth + 2][kGridHeight + 2];
	float send[kGridWidth][kGridHeight];
	float recv[kGridWidth][kGridHeight];
	float s1[NXDIM][NYDIM];
	int x, y;

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
	// void bc(int nxdim, int nydim, float s1[nxdim][nydim], 
	// 	int i1, int i2, int j1, int j2);
	void stats(int nxdim, int nydim, float s2[nxdim][nydim], 
			int i1, int i2, int j1, int j2, int nx, 
			int n, float dt, float *smax, float *smin);
    // void sfc(int nx, int ny, int nymax, float splot[NX][NY], float simtime,
	// 		float angh, float angv, char *label, char *name);
	void advection(int nxdim, int nydim, int nx, int ny, float s1[nxdim][nydim], 
				float u[nx+1][ny], float v[nx][ny+1], float dt, float dx, 
				int i1, int i2, int j1, int j2);
	void send_ghosts(int tag, int w, int h, float src[w + 2][h + 2], float rowBuf[w], 
					float colBuf[h]);
	void recv_ghosts(int tag, int w, int h, float dst[w + 2][h + 2], float rowBuf[w], 
					float colBuf[h]);

/* Parameters and input .................................... */
	/*printf("NX=%d, BC_WIDTH=%d, I1=%d, I2=%d, NXDIM=%d\n",
		NX,BC_WIDTH,I1,I2,NXDIM);*/

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

	/*c = 1.0;*/
	pi = 4.0*atan(1.0);
    dt = pi/nstep;
    dx=1.0/(NX-1);
    dy=1.0/(NY-1);

/*
 * Set the initial condition
 */
	ic(GRID_XDIM,GRID_YDIM,kGridWidth,kGridHeight,in,u,v,dx,dy,I1,I2,J1,J2);
	start = get_wall_time(); // Record time right after initial condition

/* Print the grid information from PE0 */
    if (kRank == 0) {
		printf("Numerical Fluid Dynamics\n\n");
		printf("NX = %4d, NY = %4d, dx = %9.5f, dy = %9.5f\n", NX, NY, dx, dy);
    	printf("[%d] there are %d pes, divided into a %d x %d grid.\n", kRank,
        		kNumPes, kGridRows, kGridCols);
		printf("[%d] each PE is taking a %d by %d tile.\n", kRank, kGridWidth, kGridHeight);
		/* Print initial condition */
		for (n = 0; n < kNumPes; n++) {
			x = (n % kGridCols) * kGridWidth;
			y = (n / kGridCols) * kGridHeight;
			printf("[%d] Receiving values from %d into (%d, %d).\n", kRank, n, x, y);
			// No receive needed for PE0 since the tile is local
			if (n == 0) {
				copy_stencil_to_buffer(kGridWidth, kGridHeight, in, recv);
			} else {
				MPI_Recv(recv, kGridWidth * kGridHeight, MPI_FLOAT, n, n, MPI_COMM_WORLD,
							MPI_STATUS_IGNORE);
			}
			copy_buffer_to_stencil(NX, NY, s1, kGridWidth, kGridHeight, recv, x, y);
		}
		printf("[%d] Initial condition:\n", kRank);
		printf("%5s %9s %9s %4s %4s %9s %4s %4s\n","Step","Time",
					"Max","at I","J","Min","at I","J");
		stats(NXDIM,NYDIM,s1,1,NX,1,NY,NX,0,dt,&smax,&smin);
    }
	else {
		copy_stencil_to_buffer(kGridWidth, kGridHeight, in, send);
		MPI_Send(send, kGridWidth * kGridHeight, MPI_FLOAT, 0, kRank, MPI_COMM_WORLD);
  	}

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
		// bc(GRID_XDIM,GRID_YDIM,in,I1,I2,J1,J2);
		send_ghosts(n, kGridWidth, kGridHeight, in, rowBuf, colBuf);
		recv_ghosts(n, kGridWidth, kGridHeight, in, rowBuf, colBuf);

/*  . . . Compute values at next step				*/
	   	advection(GRID_XDIM,GRID_YDIM,kGridWidth,kGridHeight,in,
					u,v,dt,dx,I1,I2,J1,J2);

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
/* Wait for all of the threads to finish communication */
	MPI_Barrier(MPI_COMM_WORLD);
	end = get_wall_time(); // Get time after finishing for loop

/* Collect the results at the root */
	if (kRank == 0) {
		for (n = 0; n < kNumPes; n++) {
			x = (n % kGridCols) * kGridWidth;
			y = (n / kGridCols) * kGridHeight;
			printf("[%d] Receiving values from %d into (%d, %d).\n", kRank, n, x, y);
			// No receive needed for PE0 since the tile is local
			if (n == 0) {
				copy_stencil_to_buffer(kGridWidth, kGridHeight, in, recv);
			} else {
				MPI_Recv(recv, kGridWidth * kGridHeight, MPI_FLOAT, n, n, MPI_COMM_WORLD,
							MPI_STATUS_IGNORE);
			}
			copy_buffer_to_stencil(NX, NY, s1, kGridWidth, kGridHeight, recv, x, y);
		}
/* Print the final results to validate the code with serial version */
		printf("[%d] Final results:\n", kRank);
		printf("%5s %9s %9s %4s %4s %9s %4s %4s\n","Step","Time",
					"Max","at I","J","Min","at I","J");
		stats(NXDIM,NYDIM,s1,1,NX,1,NY,NX,nstep,dt,&smax,&smin);
		printf("[%d] It took %.6lf seconds.\n", kRank, end - start);
  	}
	else {
		copy_stencil_to_buffer(kGridWidth, kGridHeight, in, send);
		MPI_Send(send, kGridWidth * kGridHeight, MPI_FLOAT, 0, kRank, MPI_COMM_WORLD);
  	}
		

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

	// teminate normally
	MPI_Finalize();
	exit(0);
}
