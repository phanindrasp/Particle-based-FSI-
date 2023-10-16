#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils_RBF.h"


void eval_f_force(int i,int j,float rx,float ry,float rvx,float rvy,char lbl)
{

  if (lbl=='f')
  {

   r=sqrt(pow(rx,2)+pow(ry,2));
   q=r/h;

   phi=((rx*rvx+ry*rvy)/(pow(r,2)+0.001*pow(h,2)));

         if(r<=h && r>1e-8)
         {
         // Gradient of smoothing kernel function
         DWx1=(10/(3.14*7*pow(h,3)))*(-3*q+(9.f/4.f)*(pow(q,2)))*rx/r;
         DWy1=(10/(3.14*7*pow(h,3)))*(-3*q+(9.f/4.f)*(pow(q,2)))*ry/r;


         // Continuity equation
         //*(rho+i)+=dt*(*(rho+i)*(m/(*(rho+j)))*(rvx*DWx1+rvy*DWy1));
         // Momentum equation (pressure gradient)

         (fp+i)->F[0]+=-mf*(mf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((fp+j)->P/(pow((fp+j)->rho,2))))*DWx1);
         (fp+i)->F[1]+=-mf*(mf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((fp+j)->P/(pow((fp+j)->rho,2))))*DWy1);

         // Momentum equation (viscous stress term)

if(rx*rvx+ry*rvy<0)
{
           (fp+i)->F[0]+=mf*mf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(fp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(fp+j)->rho))*DWx1);
           (fp+i)->F[1]+=mf*mf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(fp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(fp+j)->rho))*DWy1);
}

         }


         else if(r>h && r<=2*h && r>1e-8)
         {

          // Gradient of smoothing kernel function
          DWx2=-(15.f/(14.f*3.14*pow(h,3)))*(pow(2-q,2))*rx/r;
          DWy2=-(15.f/(14.f*3.14*pow(h,3)))*(pow(2-q,2))*ry/r;

         // Continuity equation
         //*(rho+i)+=dt*(*(rho+i)*(m/(*(rho+j)))*(rvx*DWx2+rvy*DWy2));
         // Momentum equation (pressure gradient)

          (fp+i)->F[0]+=-mf*(mf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((fp+j)->P/(pow((fp+j)->rho,2))))*DWx2);
          (fp+i)->F[1]+=-mf*(mf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((fp+j)->P/(pow((fp+j)->rho,2))))*DWy2);

//printf("1 is %d %f %f\n",i,(fp+i)->F[0],(fp+i)->F[1]);
if(rx*rvx+ry*rvy<0)
{ 
          (fp+i)->F[0]+=mf*mf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(fp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(fp+j)->rho))*DWx2);
          (fp+i)->F[1]+=mf*mf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(fp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(fp+j)->rho))*DWy2);
}
//printf("2 is %d %f %f\n",i,(fp+i)->F[0],(fp+i)->F[1]);
         }


}



else if(lbl=='s')
{

   r=sqrt(pow(rx,2)+pow(ry,2));
   q=r/h;

   phi=((rx*rvx+ry*rvy)/(pow(r,2)+0.001*pow(h,2)));

         if(r<=h && r>1e-8)
         {
         // Gradient of smoothing kernel function
         DWx1=(10/(3.14*7*pow(h,3)))*(-3*q+(9.f/4.f)*(pow(q,2)))*rx/r;
         DWy1=(10/(3.14*7*pow(h,3)))*(-3*q+(9.f/4.f)*(pow(q,2)))*ry/r;


         // Continuity equation
         //*(rho+i)+=dt*(*(rho+i)*(m/(*(rho+j)))*(rvx*DWx1+rvy*DWy1));
         // Momentum equation (pressure gradient)

         (fp+i)->F[0]+=-mf*(msf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((sp+j)->P/(pow((sp+j)->rho,2))))*DWx1);
         (fp+i)->F[1]+=-mf*(msf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((sp+j)->P/(pow((sp+j)->rho,2))))*DWy1);

         (sp+j)->F[0]+=mf*(msf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((sp+j)->P/(pow((sp+j)->rho,2))))*DWx1);
         (sp+j)->F[1]+=mf*(msf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((sp+j)->P/(pow((sp+j)->rho,2))))*DWy1);

      //   printf("in 1 pre force %d %f %f\n",j,m*(m*(((fp+i)->P/(pow((fp+i)->rho,2)))+((ip+j)->P/(pow((ip+j)->rho,2))))*DWx1),m*(m*(((fp+i)->P/(pow((fp+i)->rho,2)))+((ip+j)->P/(pow((ip+j)->rho,2))))*DWy1));


         // Momentum equation (viscous stress term)
 
if(rx*rvx+ry*rvy<0)
{          
           (fp+i)->F[0]+=mf*msf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(sp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(sp+j)->rho))*DWx1);
           (fp+i)->F[1]+=mf*msf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(sp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(sp+j)->rho))*DWy1);

           (sp+j)->F[0]+=-mf*msf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(sp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(sp+j)->rho))*DWx1);
           (sp+j)->F[1]+=-mf*msf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(sp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(sp+j)->rho))*DWy1);
}
       //  printf("in 1 visc force %d %f %f\n",j,-m*(2*mu*(m/(( (fp+i)->rho)*((ip+j)->rho)))*((rx*DWx1+ry*DWy1)/(pow(r,2)+0.001*pow(h,2)))*rvx),-m*(2*mu*(m/(( (fp+i)->rho)*((ip+j)->rho)))*((rx*DWx1+ry*DWy1)/(pow(r,2)+0.001*pow(h,2)))*rvy));

         }


         else if(r>h && r<=2*h && r>1e-8)
         {

          // Gradient of smoothing kernel function
          DWx2=-(15.f/(14.f*3.14*pow(h,3)))*(pow(2-q,2))*rx/r;
          DWy2=-(15.f/(14.f*3.14*pow(h,3)))*(pow(2-q,2))*ry/r;

         // Continuity equation
         //*(rho+i)+=dt*(*(rho+i)*(m/(*(rho+j)))*(rvx*DWx2+rvy*DWy2));
         // Momentum equation (pressure gradient)

          (fp+i)->F[0]+=-mf*(msf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((sp+j)->P/(pow((sp+j)->rho,2))))*DWx2);
          (fp+i)->F[1]+=-mf*(msf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((sp+j)->P/(pow((sp+j)->rho,2))))*DWy2);

          (sp+j)->F[0]+=mf*(msf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((sp+j)->P/(pow((sp+j)->rho,2))))*DWx2);
          (sp+j)->F[1]+=mf*(msf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((sp+j)->P/(pow((sp+j)->rho,2))))*DWy2);

//printf("in 2 pre force %d %f %f\n",j,m*(m*(((fp+i)->P/(pow((fp+i)->rho,2)))+((ip+j)->P/(pow((ip+j)->rho,2))))*DWx1),m*(m*(((fp+i)->P/(pow((fp+i)->rho,2)))+((ip+j)->P/(pow((ip+j)->rho,2))))*DWy1));
if(rx*rvx+ry*rvy<0)
{ 

           (fp+i)->F[0]+=mf*msf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(sp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(sp+j)->rho))*DWx2);
           (fp+i)->F[1]+=mf*msf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(sp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(sp+j)->rho))*DWy2);

           (sp+j)->F[0]+=-mf*msf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(sp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(sp+j)->rho))*DWx2);
           (sp+j)->F[1]+=-mf*msf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(sp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(sp+j)->rho))*DWy2);
}
//printf("in 1 visc force %d %f %f\n",j,-m*(2*mu*(m/(( (fp+i)->rho)*((ip+j)->rho)))*((rx*DWx1+ry*DWy1)/(pow(r,2)+0.001*pow(h,2)))*rvx),-m*(2*mu*(m/(( (fp+i)->rho)*((ip+j)->rho)))*((rx*DWx1+ry*DWy1)/(pow(r,2)+0.001*pow(h,2)))*rvy));
         }



}



else if(lbl=='w')
{

   r=sqrt(pow(rx,2)+pow(ry,2));
   q=r/h;

   phi=((rx*rvx+ry*rvy)/(pow(r,2)+0.001*pow(h,2)));

         if(r<=h && r>1e-8)
         {
         // Gradient of smoothing kernel function
         DWx1=(10/(3.14*7*pow(h,3)))*(-3*q+(9.f/4.f)*(pow(q,2)))*rx/r;
         DWy1=(10/(3.14*7*pow(h,3)))*(-3*q+(9.f/4.f)*(pow(q,2)))*ry/r;


         // Continuity equation
         //*(rho+i)+=dt*(*(rho+i)*(m/(*(rho+j)))*(rvx*DWx1+rvy*DWy1));
         // Momentum equation (pressure gradient)

         (fp+i)->F[0]+=-mf*(mf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((wp+j)->P/(pow((wp+j)->rho,2))))*DWx1);
         (fp+i)->F[1]+=-mf*(mf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((wp+j)->P/(pow((wp+j)->rho,2))))*DWy1);


      //   printf("in 1 pre force %d %f %f\n",j,m*(m*(((fp+i)->P/(pow((fp+i)->rho,2)))+((ip+j)->P/(pow((ip+j)->rho,2))))*DWx1),m*(m*(((fp+i)->P/(pow((fp+i)->rho,2)))+((ip+j)->P/(pow((ip+j)->rho,2))))*DWy1));


         // Momentum equation (viscous stress term)
if(rx*rvx+ry*rvy<0)
{
 
           (fp+i)->F[0]+=mf*mf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(wp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(wp+j)->rho))*DWx1);
           (fp+i)->F[1]+=mf*mf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(wp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(wp+j)->rho))*DWy1);
}

       //  printf("in 1 visc force %d %f %f\n",j,-m*(2*mu*(m/(( (fp+i)->rho)*((ip+j)->rho)))*((rx*DWx1+ry*DWy1)/(pow(r,2)+0.001*pow(h,2)))*rvx),-m*(2*mu*(m/(( (fp+i)->rho)*((ip+j)->rho)))*((rx*DWx1+ry*DWy1)/(pow(r,2)+0.001*pow(h,2)))*rvy));

         }


         else if(r>h && r<=2*h && r>1e-8)
         {

          // Gradient of smoothing kernel function
          DWx2=-(15.f/(14.f*3.14*pow(h,3)))*(pow(2-q,2))*rx/r;
          DWy2=-(15.f/(14.f*3.14*pow(h,3)))*(pow(2-q,2))*ry/r;

         // Continuity equation
         //*(rho+i)+=dt*(*(rho+i)*(m/(*(rho+j)))*(rvx*DWx2+rvy*DWy2));
         // Momentum equation (pressure gradient)

          (fp+i)->F[0]+=-mf*(mf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((wp+j)->P/(pow((wp+j)->rho,2))))*DWx2);
          (fp+i)->F[1]+=-mf*(mf*(((fp+i)->P/(pow((fp+i)->rho,2)))+((wp+j)->P/(pow((wp+j)->rho,2))))*DWy2);


//printf("in 2 pre force %d %f %f\n",j,m*(m*(((fp+i)->P/(pow((fp+i)->rho,2)))+((ip+j)->P/(pow((ip+j)->rho,2))))*DWx1),m*(m*(((fp+i)->P/(pow((fp+i)->rho,2)))+((ip+j)->P/(pow((ip+j)->rho,2))))*DWy1));
if(rx*rvx+ry*rvy<0)
{
 
           (fp+i)->F[0]+=mf*mf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(wp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(wp+j)->rho))*DWx2);
           (fp+i)->F[1]+=mf*mf*((16*mu*(1/(((fp+i)->rho)*((fp+i)->rho+(wp+j)->rho)))*phi+2*h*h*beta*pow(phi,2)/((fp+i)->rho+(wp+j)->rho))*DWy2);
}
//printf("in 1 visc force %d %f %f\n",j,-m*(2*mu*(m/(( (fp+i)->rho)*((ip+j)->rho)))*((rx*DWx1+ry*DWy1)/(pow(r,2)+0.001*pow(h,2)))*rvx),-m*(2*mu*(m/(( (fp+i)->rho)*((ip+j)->rho)))*((rx*DWx1+ry*DWy1)/(pow(r,2)+0.001*pow(h,2)))*rvy));
         }



}

}
