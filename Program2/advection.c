#include "constants"
void advect1d(float s1d_out[],float s1d_in[],float u1d[],float dx, float dt,int i1, int i2, int nx,int advection_type);
void advection(float s1[][NYDIM],float u[][NY],float v[][NY+1],float dt,float dx,int advection_type)/*how do I know the arguments here*/
{

/*void advect1d(float s1d_out[],float s1d_in[],float u1d[],float dx, float dt,int i1, int i2, int nx,int advection_type);*/ /*define here advect1d as prototype*/
float courant,sigma;
float s1d_in[NXDIM],s1d_out[NXDIM],u1d[NX+1];
int i,j;
for (j=J1;j<=J2;j++){
      for (i=0;i<NXDIM;i++){
        s1d_in[i]=s1[i][j];}

           for(i=0;i<NX+1;i++){
              u1d[i]=u[i][j-J1];}

        advect1d(s1d_out,s1d_in,u1d,dx,dt,I1,I2,NX,advection_type);/* do i need dimensions here also*/
       for(i=I1;i<=I2;i++){
           s1[i][j]=s1d_out[i];}/*why does i gofrom I1 to I2 here while as in the above s1d_in loop it goes from 0-nxdim*/
}
  

for (i=I1;i<=I2;i++){
      for(j=0;j<NYDIM;j++){
         s1d_in[j]=s1[i][j];}
          
            for(j=0;j<NY+1;j++){
              u1d[j]=v[i-I1][j];}
        advect1d(s1d_out,s1d_in,u1d,dx,dt,J1,J2,NY,advection_type);
     for(j=J1;j<=J2;j++){
        s1[i][j]=s1d_in[j];}
}return;
}/*last bracket not lit up*/
   
    
