#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils_RBF.h"


void eval_mass()
{


rx=(fp+1)->x[0]-(fp+0)->x[0];
ry=(fp+1)->x[1]-(fp+0)->x[1];
af=sqrt(pow(rx,2)+pow(ry,2));

rc=2*af;
rco=af;
h=rc/2;

eval_neighs_opt();


int i=Nf/2;
int j;
char lbl;
float rhot=0;

tempnode=(fp+i)->neighs;


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

    // Evaluate densities and pressures of particles

            if(r<=h)
            {
                 rhot+=W1;

            }

           else
            {
                 rhot+=W2;

            }

         }


   if (lbl=='w')
        {

        rx=(fp+i)->x[0]-(wp+j)->x[0];
        ry=(fp+i)->x[1]-(wp+j)->x[1];
        r=sqrt(pow(rx,2)+pow(ry,2));

        q=r/h;

        // Kernel function
        W1=(10/(3.14*7*pow(h,2)))*(1-1.5*pow(q,2)+0.75*(pow(q,3)));
        W2=(5/(3.14*14*pow(h,2)))*(pow(2-q,3));

    // Evaluate densities and pressures of particles

            if(r<=h)
            {
                 rhot+=W1;

            }

           else
            {
                 rhot+=W2;

            }

         }

   if (lbl=='s')
        {

        rx=(fp+i)->x[0]-(sp+j)->x[0];
        ry=(fp+i)->x[1]-(sp+j)->x[1];
        r=sqrt(pow(rx,2)+pow(ry,2));

        q=r/h;

        // Kernel function
        W1=(10/(3.14*7*pow(h,2)))*(1-1.5*pow(q,2)+0.75*(pow(q,3)));
        W2=(5/(3.14*14*pow(h,2)))*(pow(2-q,3));

    // Evaluate densities and pressures of particles

            if(r<=h)
            {
                 rhot+=W1;

            }

           else
            {
                 rhot+=W2;

            }

         }


        tempnode=tempnode->next;

 }


rx=(sp+1)->x[0]-(sp+0)->x[0];
ry=(sp+1)->x[1]-(sp+0)->x[1];
as=sqrt(pow(rx,2)+pow(ry,2));

mf=rho0/rhot;
msf=mf*pow(as/af,2);



}
