/*
 * HERE is what you need to call the contour ("contr") and surface ("sfc") routines in Pgm #2
 */

/*
 * First do this:
 *  1. DELETE the history[][] array and its use in the program.
 *       ... When we call sfc() now, we'll do it with a 2-d (X,Y) solution array.
 *  2. Change your Makefile: add contr.o to OBJECTS, and contr.c to SOURCE
 *  3. Add the code bits below.
 */


/*
 * Definitions you will need near the top of your code
 * New part is Y dimension.  
 * NOTE: NY will not always equal NX !!!
 */

#define NX whatever-value-you-want-CHANGE-this
#define NY NX
#define BC_WIDTH 1
#define I1 BC_WIDTH
#define I2 I1+NX-1
#define J1 BC_WIDTH
#define J2 J1+NY-1
#define NXDIM NX+2*BC_WIDTH
#define NYDIM NY+2*BC_WIDTH

/*
 * Variables you will need to add to your main program
 */

	int colors,pltzero;
	char title[25];
	float cint,simtime,angh,angv;
     	float s1[NXDIM][NYDIM]; /* and s2 etc ... */
	float splot[NX][NY];

/*
 * Add this to your function prototype definitions
 */

void contr(int nx,int ny,float splot[NX][NY],float cint,float simtime,
           char *title,int colors,int pltzero,int nestX1,int nestX2,
           int nestY1,int nestY2,char *name);
/**REPLACE** your old sfc() prototype with the one below - and delete this comment. */
void sfc(int nx,int ny,int nymax,float splot[NX][NY],float simtime,
         float angh,float angv,char *label,char *name);

/*
 * Plot contours
 * n is our loop counter in the full code (use "0" for initial condition)
 * cint is contour interval ( 5.0 = plot contours at -10, -5, +5, +10, ... )
 * simtime is the integration time in seconds
 * colors is the color setting in the contr routine, 0=default
 * title is the contour/sfc text plotted at the top
 * name is Your name, as usual, in your main program
 * pltzero, if false, skips plotting the zero contour (recommended)
 */

	printf("Plotting contours.\n");	/* delete this when contour plots are working */

	for (j=J1; j<=J2; j++) {	/* copy s1 to NX,NY plotting array */
	  for (i=I1; i<=I2; i++) {
	    splot[i-I1][j-J1] = s1[i][j]; } } /* works for any BC_WIDTH */

	cint    = 1.0;	/* contour interval */
	colors  =   0;	/* positive values colored red, negative blue, all solid */
	pltzero =  -1;	/* don't plot the often noisy zero line */
	simtime = dt*(float)n;
	sprintf(title,"Contour plot at n = %d",n);
	contr(NX,NY,splot,cint,simtime,title,colors,pltzero,0,0,0,0,name);

/*
 * Plot surface
 * angh is horizontal viewing angle, degrees, counter-clockwise from X-axis
 * angv is vertical   viewing angle above x-y plane
 */

	printf("Plotting surface.\n");	/* delete this when sfc plots are working */

	for (j=J1; j<=J2; j++) {	/* copy s1>splot if you haven't already done it */
	  for (i=I1; i<=I2; i++) {
	    splot[i-I1][j-J1] = s1[i][j]; } } /* works for any BC_WIDTH */

	angh = -45.0;
	angv =  20.0;
	sprintf(title,"Surface plot at n = %d",n);
	sfc(NX,NY,NY,splot,simtime,angh,angv,title,name);
