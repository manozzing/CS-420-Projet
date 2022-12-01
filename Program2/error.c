/* dispersion and dissipation errors tacaks*/
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
void error(float sd[nx][ny],float st[nx][ny],int i1,int i2,int ji,int j2,int nx,int ny,float rho,float total_error,float dissipation_error,float dispersion_error)
{
  int i,j;
  float sd_sum,sd_mean,st_sum,st_mean,sd_var,st_var,a,b,c,d;
  sd_sum,sd_mean,st_sum,st_mean,sd_var,st_var,a,b,c,d=0;

for(i=i1;i<=i2;i++){
   for(j=j1;j<=j2;j++){
       sd_sum=sd_sum+sd[i][j];
       st_sum=st_sum+st[i][j];
}}
sd_mean=sd_sum/(nx*ny);
st_mean=st_sum/(nx*ny);
for(i=i1;i<=i2;i++){
   for(j=j1;j<=j2;j++){
      a=a+(sd[i][j]-sd_mean)*(st[i][j]-st_mean);
      b=b+pow((sd[i][j]-sd_mean),2);
      c=c+pow((st[i][j]-st_mean),2);
      d=d+pow((st[i][j]-sd[i][j]),2);}}
rho=a/sqrt(b*c);
total_error=d/(nx*ny);
sd_var=sqrt(b/(nx*ny));
st_var=sqrt(c/(nx*ny));
dissipation_error=pow((sd_var-st_var),2)+pow((sd_mean-st_mean),2);
dispersion_error=2*(1-rho)*sd_var*st_var;
printf("Tkacs error values");
printf("correlation coefficient=%f",rho);
printf("\n");
printf("Total Error=%f\n Dissipation Error=%f\n Dispersion Error=%f",total_error,dissipation_error,dispersion_error);
