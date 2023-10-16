#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils_RBF.h"
#include <omp.h>

void eval_density()
{

int j;
char lbl;

   // Traverse through the neighbor list for fluids
   for(int i=0;i<Nf;i++)
   {

      (fp+i)->rho=0;

      tempnode=(fp+i)->neighs;
     // printf("%d %p\n",i,tempnode->next);

      while (tempnode!=NULL && tempnode->index!=-1)
      {
        j=tempnode->index;
        lbl=tempnode->label;

        if (lbl=='f')
        {

        rx=(fp+i)->x[0]-(fp+j)->x[0];
        ry=(fp+i)->x[1]-(fp+j)->x[1];
        r=sqrt(pow(rx,2)+pow(ry,2));

        q=r/h;

        // Kernel function
        W1=(10/(3.14*7*pow(h,2)))*(1-1.5*pow(q,2)+0.75*(pow(q,3)));
        W2=(5/(3.14*14*pow(h,2)))*(pow(2-q,3));

     //  printf("%f %f\n",W1,W2);
    // Evaluate densities and pressures of particles

          if(r<=h)
          {
                 (fp+i)->rho+=mf*W1;

          }

         else
          {
                 (fp+i)->rho+=mf*W2;

          }

         }



      else if (lbl=='w')
        {

        rx=(fp+i)->x[0]-(wp+j)->x[0];
        ry=(fp+i)->x[1]-(wp+j)->x[1];
        r=sqrt(pow(rx,2)+pow(ry,2));

        q=r/h;

        // Kernel function
        W1=(10/(3.14*7*pow(h,2)))*(1-1.5*pow(q,2)+0.75*(pow(q,3)));
        W2=(5/(3.14*14*pow(h,2)))*(pow(2-q,3));

     //  printf("%f %f\n",W1,W2);
    // Evaluate densities and pressures of particles

          if(r<=h)
          {
                 (fp+i)->rho+=mf*W1;

          }

         else
          {
                 (fp+i)->rho+=mf*W2;

          }

         }

     else if (lbl=='s')
        {

        rx=(fp+i)->x[0]-(sp+j)->x[0];
        ry=(fp+i)->x[1]-(sp+j)->x[1];
        r=sqrt(pow(rx,2)+pow(ry,2));

        q=r/h;

        // Kernel function
        W1=(10/(3.14*7*pow(h,2)))*(1-1.5*pow(q,2)+0.75*(pow(q,3)));
        W2=(5/(3.14*14*pow(h,2)))*(pow(2-q,3));

     //  printf("%f %f\n",W1,W2);
    // Evaluate densities and pressures of particles

          if(r<=h)
          {
                 (fp+i)->rho+=msf*W1;

          }

         else
          {
                 (fp+i)->rho+=msf*W2;

          }

         } 


          // Move to the next neighbor
         tempnode=tempnode->next;
       }
  //   printf("%d %f\n",i,(fp+i)->rho);

       if((fp+i)->rho<rho0)
        {
        (fp+i)->rho=rho0;
        }


        (fp+i)->P=k*(pow(((fp+i)->rho/rho0),gam)-1);


        //(fp+i)->P=k*((fp+i)->rho-rho0);
        // printf("Fluid density %d %f\n",i,(fp+i)->rho);

       }

// Traverse through the neighbor list for wall particles
   for(int i=0;i<Nw;i++)
   {

      (wp+i)->rho=0;

      tempnode=(wp+i)->neighs;


      while (tempnode!=NULL && tempnode->index!=-1)
      {
        j=tempnode->index;
        lbl=tempnode->label;

        if (lbl=='f')
        {

        rx=(wp+i)->x[0]-(fp+j)->x[0];
        ry=(wp+i)->x[1]-(fp+j)->x[1];
        r=sqrt(pow(rx,2)+pow(ry,2));

        q=r/h;

        // Kernel function
        W1=(10/(3.14*7*pow(h,2)))*(1-1.5*pow(q,2)+0.75*(pow(q,3)));
        W2=(5/(3.14*14*pow(h,2)))*(pow(2-q,3));

     //  printf("%f %f\n",W1,W2);
    // Evaluate densities and pressures of particles

          if(r<=h)
          {
                 (wp+i)->rho+=mf*W1;

          }

         else
          {
                 (wp+i)->rho+=mf*W2;

          }

         }


      else if (lbl=='w')
        {

        rx=(wp+i)->x[0]-(wp+j)->x[0];
        ry=(wp+i)->x[1]-(wp+j)->x[1];
        r=sqrt(pow(rx,2)+pow(ry,2));

        q=r/h;

        // Kernel function
        W1=(10/(3.14*7*pow(h,2)))*(1-1.5*pow(q,2)+0.75*(pow(q,3)));
        W2=(5/(3.14*14*pow(h,2)))*(pow(2-q,3));

     //  printf("%f %f\n",W1,W2);
    // Evaluate densities and pressures of particles

          if(r<=h)
          {
                 (wp+i)->rho+=mf*W1;

          }

         else
          {
                 (wp+i)->rho+=mf*W2;

          }

         }

     else if (lbl=='s')
        {

        rx=(wp+i)->x[0]-(sp+j)->x[0];
        ry=(wp+i)->x[1]-(sp+j)->x[1];
        r=sqrt(pow(rx,2)+pow(ry,2));

        q=r/h;

        // Kernel function
        W1=(10/(3.14*7*pow(h,2)))*(1-1.5*pow(q,2)+0.75*(pow(q,3)));
        W2=(5/(3.14*14*pow(h,2)))*(pow(2-q,3));

     //  printf("%f %f\n",W1,W2);
    // Evaluate densities and pressures of particles

          if(r<=h)
          {
                 (wp+i)->rho+=msf*W1;

          }

         else
          {
                 (wp+i)->rho+=msf*W2;

          }

         }


          // Move to the next neighbor
         tempnode=tempnode->next;
       }
  //   printf("%d %f\n",i,(fp+i)->rho);

       if((wp+i)->rho<rho0)
        {
         (wp+i)->rho=rho0;
        }


        (wp+i)->P=k*(pow(((wp+i)->rho/rho0),gam)-1);


        //(fp+i)->P=k*((fp+i)->rho-rho0);
        // printf("Fluid density %d %f\n",i,(fp+i)->rho);

       }





// Traverse through the neighbor list for solid particles

   for(int i=0;i<Ns;i++)
   {

      (sp+i)->rho=0;

      tempnode=(sp+i)->neighs;


      while (tempnode!=NULL && tempnode->index!=-1)
      {
        j=tempnode->index;
        lbl=tempnode->label;

        if (lbl=='f')
        {

        rx=(sp+i)->x[0]-(fp+j)->x[0];
        ry=(sp+i)->x[1]-(fp+j)->x[1];
        r=sqrt(pow(rx,2)+pow(ry,2));

        q=r/h;

        // Kernel function
        W1=(10/(3.14*7*pow(h,2)))*(1-1.5*pow(q,2)+0.75*(pow(q,3)));
        W2=(5/(3.14*14*pow(h,2)))*(pow(2-q,3));

     //  printf("%f %f\n",W1,W2);
    // Evaluate densities and pressures of particles

          if(r<=h)
          {
                 (sp+i)->rho+=mf*W1;

          }

         else
          {
                 (sp+i)->rho+=mf*W2;

          }

         }


          else if (lbl=='w')
        {

        rx=(sp+i)->x[0]-(wp+j)->x[0];
        ry=(sp+i)->x[1]-(wp+j)->x[1];
        r=sqrt(pow(rx,2)+pow(ry,2));

        q=r/h;

        // Kernel function
        W1=(10/(3.14*7*pow(h,2)))*(1-1.5*pow(q,2)+0.75*(pow(q,3)));
        W2=(5/(3.14*14*pow(h,2)))*(pow(2-q,3));

     //  printf("%f %f\n",W1,W2);
    // Evaluate densities and pressures of particles

          if(r<=h)
          {
                 (sp+i)->rho+=mf*W1;

          }

         else
          {
                 (sp+i)->rho+=mf*W2;

          }

         }

     else if (lbl=='s')
        {

        rx=(sp+i)->x[0]-(sp+j)->x[0];
        ry=(sp+i)->x[1]-(sp+j)->x[1];
        r=sqrt(pow(rx,2)+pow(ry,2));

        q=r/h;

        // Kernel function
        W1=(10/(3.14*7*pow(h,2)))*(1-1.5*pow(q,2)+0.75*(pow(q,3)));
        W2=(5/(3.14*14*pow(h,2)))*(pow(2-q,3));

     //  printf("%f %f\n",W1,W2);
    // Evaluate densities and pressures of particles

          if(r<=h)
          {
                 (sp+i)->rho+=msf*W1;

          }

         else
          {
                 (sp+i)->rho+=msf*W2;

          }

       }


          // Move to the next neighbor
         tempnode=tempnode->next;
       }
  //   printf("%d %f\n",i,(fp+i)->rho);

       if((sp+i)->rho<rho0)
        {
         (sp+i)->rho=rho0;
        }


        (sp+i)->P=k*(pow(((sp+i)->rho/rho0),gam)-1);


        //(fp+i)->P=k*((fp+i)->rho-rho0);
        // printf("solid density %d %f\n",i,(sp+i)->rho);

       }



}
