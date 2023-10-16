#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils_RBF.h"

void read_points()
{

float temp1,temp2;
int temp3,temp4,temp5;
char lbl;

Nf=0;
Nw=0;
Ns=0;


int jf=0;
int jw=0;
int js=0;

FILE *fptr;
FILE *fptr1;

fptr=fopen("/home/user/Documents/Phani/PFSI_paper1/data/points.csv","r");
fptr1=fopen("/home/user/Documents/Phani/PFSI_paper1/data/points_nodes.txt","w");

//fptr=fopen("/home/user/Documents/Phani/PFSI_paper1/Parametric_study/1/points.csv","r");
//fptr1=fopen("/home/user/Documents/Phani/PFSI_paper1/Parametric_study/1/points_nodes.txt","w");

 while(fscanf(fptr,"%f,%f,%c",&temp1,&temp2,&lbl)!=EOF)
 {


    if(lbl=='f')
    {
     Nf++;
    }

    else if(lbl=='w')
    {
     Nw++;
    }

    else if(lbl=='s')
    {
     Ns++;
    }

 }



/*
pos[0]=0.025;
pos[1]=0.1;
*/

// Create an a structure array to store first element of linked lists (one linked list for each cell)
// and allocate memory
   //cell= (struct cell_list*)malloc(Nc*sizeof(struct cell_list));

// Allocate memory to the arrays

    //label=(char *)malloc((Nf+Nw+Ni)*sizeof(char));
    fp=(struct fluid_particle*)malloc((Nf)*sizeof(struct fluid_particle));
    wp=(struct wall_particle*)malloc((Nw)*sizeof(struct wall_particle));
    sp=(struct solid_particle*)malloc((Ns)*sizeof(struct solid_particle));


// Go to the beginning of the file
    rewind(fptr);


// Fill the label array

 int i=0;


// Read particles

   while(fscanf(fptr,"%f,%f,%c",&temp1,&temp2,&lbl)!=EOF)
 {   

       if(lbl=='f')
      {
       (fp+jf)->x[0]=temp1;
       (fp+jf)->x[1]=temp2;
       (fp+jf)->v[0]=0;
       (fp+jf)->v[1]=0;
       (fp+jf)->F[0]=0;
       (fp+jf)->F[1]=0;
       (fp+jf)->rho=rho0;
       (fp+jf)->P=0;
       (fp+jf)->neighs=NULL;
        jf++;
      }


      else if(lbl=='w')
      {

       (wp+jw)->x[0]=temp1;
       (wp+jw)->x[1]=temp2;
       (wp+jw)->v[0]=0;
       (wp+jw)->v[1]=0;
       (wp+jw)->F[0]=0;
       (wp+jw)->F[1]=0;
       (wp+jw)->rho=rho0;
       (wp+jw)->P=0;
       (wp+jw)->neighs=NULL;
        jw++;
      }

       else if(lbl=='s')
      {

       (sp+js)->x[0]=temp1;
       (sp+js)->x0[0]=temp1;
       (sp+js)->x[1]=temp2;
       (sp+js)->x0[1]=temp2;
       (sp+js)->v[0]=0;
       (sp+js)->v[1]=0;
       (sp+js)->F[0]=0;
       (sp+js)->F[1]=0;
       (sp+js)->rho=rho0;
       (sp+js)->P=0;
       (sp+js)->Nse=0;
       (sp+js)->neighs=NULL;
      // fprintf(fptr1,"%f %f\n",temp1,temp2);
        js++;
      }


    }

fclose(fptr);
//fclose(fptr1);

//DT();


// Find domain length and width

float tmin1=wp->x[0];
float tmin2=wp->x[1];
float tmax1=wp->x[0];
float tmax2=wp->x[1];

    for (i=1;i<Nw;i++)
    {
     if((wp+i)->x[0]<tmin1)
     {
         tmin1=(wp+i)->x[0];
     }

     if((wp+i)->x[0]>tmax1)
     {
         tmax1=(wp+i)->x[0];
     }

     if((wp+i)->x[1]<tmin2)
     {
         tmin2=(wp+i)->x[1];
     }

     if((wp+i)->x[1]>tmax2)
     {
         tmax2=(wp+i)->x[1];
     }
    }

      xmin=tmin1-0.5*fabs(tmax1-tmin1);
      xmax=tmax1+0.5*fabs(tmax1-tmin1);
      ymin=tmin2-0.5*fabs(tmax2-tmin2);
      ymax=tmax2+0.5*fabs(tmax2-tmin2);


      Lx=xmax-xmin;
      Ly=ymax-ymin;

      // Solid

C1=(int **)malloc((Ne)*sizeof(int*));

for (i=0;i<Ne;i++)
{
C1[i]=(int *)malloc((3)*sizeof(int));
}

fptr=fopen("/home/user/Documents/Phani/PFSI_paper1/data/points_elements.txt","r");

//fptr=fopen("/home/user/Documents/Phani/PFSI_paper1/Parametric_study/1/points_elements.txt","r");

 i=0;

 while(fscanf(fptr,"%d %d %d\n",&temp3,&temp4,&temp5)!=EOF)
 {

   C1[i][0]=temp3-1;
   C1[i][1]=temp4-1;
   C1[i][2]=temp5-1;

   i++;
 }


fclose(fptr);




// Calculate the maximum shared elements per node

for (int i=0;i<Ns;i++)
{

 for (int j=0;j<Ne;j++)
  {

     if (C1[j][0]==i || C1[j][1]==i || C1[j][2]==i)
      {

           (sp+i)->Nse+=1;

      }

  }
//printf("%d %d\n",i,(sp+i)->Nse);
     if((sp+i)->Nse>Nem)
      {

          Nem=(sp+i)->Nse;


      }

}

//printf("%d\n",Nem);

C2=(int **)malloc((Ns)*sizeof(int *));


for (i=0;i<Ns;i++)
{
C2[i]=(int *)malloc((Nem)*sizeof(int));
}

C3=(int **)malloc((Ns)*sizeof(int *));

for (i=0;i<Ns;i++)
{
C3[i]=(int *)malloc((2*Nem)*sizeof(int));
}


for (int i=0;i<Ns;i++)
{

 for (int j=0;j<2*Nem;j++)
  {

     C3[i][j]=-1;

  }

}



for (int i=0;i<Ns;i++)
{

 for (int j=0;j<Nem;j++)
  {

     C2[i][j]=-1;

  }

}



for (int i=0;i<Ns;i++)
{

 temp=0;

 for (int j=0;j<Ne;j++)
  {

      if (C1[j][0]==i || C1[j][1]==i || C1[j][2]==i)
       {

           C2[i][temp]=j;
          // printf("%d %d\n",i,j);

           if (C1[j][0]==i)
            {

              C3[i][2*temp]=C1[j][1];
              C3[i][2*temp+1]=C1[j][2];

            }


           else if (C1[j][1]==i)
            {

              C3[i][2*temp]=C1[j][0];
              C3[i][2*temp+1]=C1[j][2];

            }


           else
            {

              C3[i][2*temp]=C1[j][1];
              C3[i][2*temp+1]=C1[j][0];

            }

            temp+=1;

       }

  }

}

// Calculate effective area of a node using area of shared triangles

for (int i=0;i<Ns;i++)
{
   Area=0;
   for (int j=0;j<Nem;j++)
    {
      if(C3[i][2*j]!=-1 && C3[i][2*j+1]!=-1)
       {

      Area+=0.333*fabs(0.5*((sp+i)->x[0]*((sp+C3[i][2*j])->x[1]-(sp+C3[i][2*j+1])->x[1])+(sp+C3[i][2*j])->x[0]*((sp+C3[i][2*j+1])->x[1]-(sp+i)->x[1])+(sp+C3[i][2*j+1])->x[0]*((sp+i)->x[1]-(sp+C3[i][2*j])->x[1])));

       }
    }
//printf("area of %d is %f\n",i,Area);
(sp+i)->m=rhos*Area;

//printf("coeffs %d %f %f %f\n",i,(sp+i)->Q0,(sp+i)->Q1,(sp+i)->Q2);
}


fail=(int *)malloc((Ne)*sizeof(int));



}
