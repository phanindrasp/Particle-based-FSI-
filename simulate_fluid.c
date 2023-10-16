#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils_RBF.h"


void simulate_fluid()
{

eval_density();

 int j;
 char lbl;


   // Traverse through the neighbor list

 for(int i=0;i<Nf;i++)
   {

       (fp+i)->F[0]=0;
       (fp+i)->F[1]=-mf*g;

      tempnode=(fp+i)->neighs;

      while (tempnode!=NULL && tempnode->index!=-1)
      {
         j=tempnode->index;
         lbl=tempnode->label;

   //      printf("neighbor of %d is %d which is %c\n",i,j,lbl);
     //    printf("%d %d %c\n",i,j,lbl);
         // Look only for fluid neighbors
         if(lbl=='f')
         {

         // Distance and relative velocity between neighbors
         rx=(fp+i)->x[0]-(fp+j)->x[0];
         ry=(fp+i)->x[1]-(fp+j)->x[1];
         rvx=(fp+i)->v[0]-(fp+j)->v[0];
         rvy=(fp+i)->v[1]-(fp+j)->v[1];
         r=sqrt(pow(rx,2)+pow(ry,2));

         // Evaluate force on fluid
         eval_f_force(i,j,rx,ry,rvx,rvy,lbl);


         }


        if(lbl=='s')
        {

         rx=(fp+i)->x[0]-(sp+j)->x[0];
         ry=(fp+i)->x[1]-(sp+j)->x[1];
         rvx=(fp+i)->v[0]-(sp+j)->v[0];
         rvy=(fp+i)->v[1]-(sp+j)->v[1];
         r=sqrt(pow(rx,2)+pow(ry,2));


        eval_f_force(i,j,rx,ry,rvx,rvy,lbl);

  /*      if(r<rco && r>1e-8 )
        {
          // printf("heyyy");
        (fp+i)->F[0]+=kr*((pow((rco/r),12)-pow((rco/r),4))/pow(r,2))*rx;
        (fp+i)->F[1]+=kr*((pow((rco/r),12)-pow((rco/r),4))/pow(r,2))*ry;
//printf("%f %f\n",(ip+j)->F[0],(ip+j)->F[1]);
        (sp+j)->F[0]+=-kr*((pow((rco/r),12)-pow((rco/r),4))/pow(r,2))*rx;
        (sp+j)->F[1]+=-kr*((pow((rco/r),12)-pow((rco/r),4))/pow(r,2))*ry;

        } 
*/

       }


       if(lbl=='w')
        {
         rx=(fp+i)->x[0]-(wp+j)->x[0];
         ry=(fp+i)->x[1]-(wp+j)->x[1];
         rvx=(fp+i)->v[0]-(wp+j)->v[0];
         rvy=(fp+i)->v[1]-(wp+j)->v[1];
         r=sqrt(pow(rx,2)+pow(ry,2));


          eval_f_force(i,j,rx,ry,rvx,rvy,lbl);
/*
   if(r<rco && r>1e-8 )
        {
          // printf("heyyy");
        (fp+i)->F[0]+=kr*((pow((rco/r),4)-pow((rco/r),2))/pow(r,2))*rx;
        (fp+i)->F[1]+=kr*((pow((rco/r),4)-pow((rco/r),2))/pow(r,2))*ry;
//printf("%f %f\n",(ip+j)->F[0],(ip+j)->F[1]);
        (wp+j)->F[0]+=-kr*((pow((rco/r),4)-pow((rco/r),2))/pow(r,2))*rx;
        (wp+j)->F[1]+=-kr*((pow((rco/r),4)-pow((rco/r),2))/pow(r,2))*ry;
//printf("%f %f\n",(ip+j)->F[0],(ip+j)->F[1]);
        }  
*/
        }
         // Move to the next neighbor
         tempnode=tempnode->next;


   }
 //  printf("%d %f %f\n",i,*(Fx+i),*(Fy+i));

   }



}

