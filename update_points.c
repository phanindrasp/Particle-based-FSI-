#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils_RBF.h"

void update_points()
{


for (int i=0;i<Nf;i++)
    {


      (fp+i)->v[0]+=(fp+i)->F[0]*dt/mf;
      (fp+i)->v[1]+=(fp+i)->F[1]*dt/mf;

  /*    if((fp+i)->x[0]<0.0002)
      {
        (fp+i)->v[0]=0.01;
      }*/

      (fp+i)->x[0]+=(fp+i)->v[0]*dt;
      (fp+i)->x[1]+=(fp+i)->v[1]*dt;

//printf("%d %f %f\n",i,(fp+i)->F[0],(fp+i)->F[1]);

      /* Update forces to zero */

      (fp+i)->F[0]=0;
      (fp+i)->F[1]=0;

   }


/*
for (int i=0;i<312;i++)
{

      (wp+i)->F[0]=0;
      (wp+i)->F[1]=0;

      (wp+i)->v[0]=0.1;
      (wp+i)->v[1]=0;

      (wp+i)->x[0]+=(wp+i)->v[0]*dt;
      (wp+i)->x[1]+=(wp+i)->v[1]*dt;

      if((wp+i)->x[0]>0.0102){(wp+i)->x[0]-=0.0104;}
}*/



for (int i=0;i<Nw;i++)
{

      (wp+i)->F[0]=0;
      (wp+i)->F[1]=0;


     

    

}



for (int i=0;i<Ns;i++)
{

(sp+i)->v[0]+=((sp+i)->F[0]-c*(sp+i)->v[0])*dt/(sp+i)->m;
(sp+i)->x[0]+=(sp+i)->v[0]*dt;


(sp+i)->v[1]+=((sp+i)->F[1]-c*(sp+i)->v[1])*dt/(sp+i)->m;
(sp+i)->x[1]+=(sp+i)->v[1]*dt;


       (sp+i)->F[0]=0;
       (sp+i)->F[1]=0;

}



}
