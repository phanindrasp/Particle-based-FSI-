#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils_RBF.h"


void simulate_solid()
{

  
 int j;
 char lbl;
 float p1,p2;

   // Traverse through the neighbor list

 for(int i=0;i<Ns;i++)
 {

    (sp+i)->F[1]=-(sp+i)->m*g;      
    tempnode=(sp+i)->neighs;
 
    while (tempnode!=NULL && tempnode->index!=-1)
      {
         j=tempnode->index;
         lbl=tempnode->label;

   //      printf("neighbor of %d is %d which is %c\n",i,j,lbl);
     //    printf("%d %d %c\n",i,j,lbl);
         // Look only for fluid neighbors
         if(lbl=='w')
         {

         // Distance and relative velocity between neighbors
         rx=(sp+i)->x[0]-(wp+j)->x[0];
         ry=(sp+i)->x[1]-(wp+j)->x[1];
         rvx=(sp+i)->v[0]-(wp+j)->v[0];
         rvy=(sp+i)->v[1]-(wp+j)->v[1];
         r=sqrt(pow(rx,2)+pow(ry,2));

         if(r<rco && r>1e-8 )
        {
   
        (sp+i)->F[0]+=kr*rx/fabs(r);
        (sp+i)->F[1]+=kr*ry/fabs(r);

        } 
          
        }

         tempnode=tempnode->next;

     }


} 


 // Calculate forces on the solid

for (int i=0;i<Ns;i++)
{
(sp+i)->sig=0;

//printf("1 is %d %f %f\n",i,Fx[i],Fy[i]);

  for (int j=0;j<Nem;j++)
   {

      if(C3[i][2*j]!=-1 && C3[i][2*j+1]!=-1)
       {
//**************** Formulation based on Plane stress

XD = (sp+i)->x[0];
YD = (sp+i)->x[1];
XR = (sp+i)->x0[0];
YR = (sp+i)->x0[1];
XDv = (sp+C3[i][2*j])->x[0];
YDv = (sp+C3[i][2*j])->x[1];
XRv = (sp+C3[i][2*j])->x0[0];
YRv = (sp+C3[i][2*j])->x0[1];
XDh = (sp+C3[i][2*j+1])->x[0];
YDh = (sp+C3[i][2*j+1])->x[1];
XRh = (sp+C3[i][2*j+1])->x0[0];
YRh = (sp+C3[i][2*j+1])->x0[1];

//printf("%d %d %f\n",i,C3[i][2*j+1],XDh);

P = XDh-XD;
Q = YDh-YD;
R = XRh-XR;
S = YRh-YR;
T = XDv-XD;
U = YDv-YD;
V = XRv-XR;
W = YRv-YR;

//**************************************** Calculation of Strain

EXX = (pow((P*W - S*T),2) +pow((Q*W - S*U),2))/(2.0*pow((R*W-S*V),2)) -1.0/2.0;
EYY = (pow((R*T - P*V),2) +pow((R*U - Q*V),2))/(2.0*pow((R*W-S*V),2)) -1.0/2.0;
EXY = ((R*T - P*V)*(P*W - S*T) + (R*U - Q*V)*(Q*W - S*U)) / (2.0*pow((R*W-S*V),2));


//***************************************Calculation of stress

ZXX = E*EXX/(1-pow(Nu,2))+E*Nu*EYY/(1-pow(Nu,2));
ZYY = E*EYY/(1-pow(Nu,2))+E*Nu*EXX/(1-pow(Nu,2));
ZXY = G*EXY;

S_E=0.5*(ZXX*EXX+ZYY*EYY+4*ZXY*EXY);
(sp+i)->sig+=S_E;
//******************************** Derivative of strain

EYY_X = ((XRh-XRv)*(P*V - T*R))/pow((R*W-V*S),2);
EYY_Y = ((XRv-XRh)*(R*U - Q*V))/pow((R*W-V*S),2);
EXX_X = ((YRh-YRv)*(P*W - T*S))/pow((R*W-V*S),2);
EXX_Y = ((YRh-YRv)*(Q*W - S*U))/pow((R*W-V*S),2);
EXY_X = ((YRh-YRv)*(R*T - P*V) + (XRv-XRh)*(P*W - T*S))/(2.0*pow((R*W - V*S),2));
EXY_Y = ((XRv-XRh)*(Q*W - U*S) + (YRh-YRv)*(R*U - Q*V))/(2.0*pow((R*W - V*S),2));


//******************************** Derivative of stress

ZXX_X = E*EXX_X/(1-pow(Nu,2)) + E*Nu*EYY_X/(1-pow(Nu,2));
ZXX_Y = E*EXX_Y/(1-pow(Nu,2)) + E*Nu*EYY_Y/(1-pow(Nu,2));
ZYY_X = E*EYY_X/(1-pow(Nu,2)) + E*Nu*EXX_X/(1-pow(Nu,2));
ZYY_Y = E*EYY_Y/(1-pow(Nu,2)) + E*Nu*EXX_Y/(1-pow(Nu,2));
ZXY_X = G*EXY_X;
ZXY_Y = G*EXY_Y;


//******************************* Force calculation
Area = fabs(0.5*(XR*(YRh-YRv)+XRh*(YRv-YR)+XRv*(YR-YRh)));

//p1=0.5*(ZXX+ZYY)+sqrt(pow(0.5*(ZXX-ZYY),2)+pow(ZXY,2));
//p2=0.5*(ZXX+ZYY)-sqrt(pow(0.5*(ZXX-ZYY),2)+pow(ZXY,2));

//S_E = fmax(p1,p2);

//if(S_E>8e5 || fail[C2[i][j]]==1)
//{
 //printf("%f\n",S_E);
// fail[C2[i][j]]=1;
// (sp+i)->F[0]+=0;
// (sp+i)->F[1]+=0;
//}

//else
//{
(sp+i)->F[0]+= -Area*0.5*(ZXX_X*EXX + ZXX*EXX_X + ZYY_X*EYY + ZYY*EYY_X + 4*ZXY_X*EXY +    4*ZXY*EXY_X);
(sp+i)->F[1]+= -Area*0.5*(ZXX_Y*EXX + ZXX*EXX_Y + ZYY_Y*EYY + ZYY*EYY_Y + 4*ZXY_Y*EXY + 4*ZXY*EXY_Y);
//}

     }

   }

(sp+i)->sig=((sp+i)->sig)/((sp+i)->Nse);

}


for (int i=0;i<7;i++)
{
(sp+i)->F[0]=0;
(sp+i)->F[1]=0;
}
/*
(sp+1)->F[0]=0;
(sp+1)->F[1]=0;



(sp+43)->F[0]=0;
(sp+43)->F[1]=0;

(sp+44)->F[0]=0;
(sp+44)->F[1]=0;

(sp+45)->F[0]=0;
(sp+45)->F[1]=0;

(sp+46)->F[0]=0;
(sp+46)->F[1]=0;

(sp+88)->F[0]=0;
(sp+88)->F[1]=0;

(sp+89)->F[0]=0;
(sp+89)->F[1]=0;

(sp+90)->F[0]=0;
(sp+90)->F[1]=0;

(sp+91)->F[0]=0;
(sp+91)->F[1]=0;

(sp+133)->F[0]=0;
(sp+133)->F[1]=0;

(sp+134)->F[0]=0;
(sp+134)->F[1]=0;
*/
//(sp+253)->F[0]+=1e1;
}
