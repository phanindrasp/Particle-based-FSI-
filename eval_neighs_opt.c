#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils_RBF.h"
#include <omp.h>



void eval_neighs_opt()
{



// Define number of cells in x and y directions

Nx=floor(Lx/rc);
Ny=floor(Ly/rc);
int Nc=Nx*Ny;



 for(int i=0;i<Nf;i++)
	{


      tempnode1=(fp+i)->neighs;
        // Free the neighbor list

        while(tempnode1!=NULL)
        {
         //  printf("%p\n",tempnode1);
            tempnode2=tempnode1;
            tempnode1=tempnode1->next;
            free(tempnode2);
            tempnode2=NULL;

        }



	}

 for(int i=0;i<Nw;i++)
	{


      tempnode1=(wp+i)->neighs;
        // Free the neighbor list

        while(tempnode1!=NULL)
        {
         //  printf("%p\n",tempnode1);
            tempnode2=tempnode1;
            tempnode1=tempnode1->next;
            free(tempnode2);
            tempnode2=NULL;

        }



	}


	for(int i=0;i<Ns;i++)
	{


       tempnode1=(sp+i)->neighs;
        // Free the neighbor list

        while(tempnode1!=NULL)
        {
            tempnode2=tempnode1;
            tempnode1=tempnode1->next;
            free(tempnode2);
            tempnode2=NULL;

        }



	}


//printf("%f %f %d %d %d\n",Lx,Ly,Nx,Ny,Nc);
//  Allot memory to the cell linked list



// Allocate memory
headf    = (int *) malloc(sizeof(int)*(Nc));
headw    = (int *) malloc(sizeof(int)*(Nc));
heads    = (int *) malloc(sizeof(int)*(Nc));

listf   = (int *) malloc(sizeof(int)*(Nf));
listw   = (int *) malloc(sizeof(int)*(Nw));
lists   = (int *) malloc(sizeof(int)*(Ns));


for(int i=0;i<Nc;i++)
	{
		 headf[i]=-1;
                headw[i]=-1;
                heads[i]=-1;

	}


// Assign particles to cells

	totneigh=9;

//printf("%p\n",fp);

	for(int i=0;i<Nf;i++)
	{


       icell=floor(((fp+i)->x[0]-xmin)*Nx/Lx)+floor(((fp+i)->x[1]-ymin)*Ny/Ly)*Nx;
     //  printf("%d %d %f %f\n",i,icell,(fp+i)->x[0],(fp+i)->x[1]);
       listf[i] = headf[icell];
       headf[icell]=i;

	}

        for(int i=0;i<Nw;i++)
	{


       icell=floor(((wp+i)->x[0]-xmin)*Nx/Lx)+floor(((wp+i)->x[1]-ymin)*Ny/Ly)*Nx;
     //  printf("%d %d %f %f\n",i,icell,(fp+i)->x[0],(fp+i)->x[1]);
       listw[i] = headw[icell];
       headw[icell]=i;

	}

        for(int i=0;i<Ns;i++)
	{


       icell=floor(((sp+i)->x[0]-xmin)*Nx/Lx)+floor(((sp+i)->x[1]-ymin)*Ny/Ly)*Nx;
     //  printf("%d %d %f %f\n",i,icell,(fp+i)->x[0],(fp+i)->x[1]);
       lists[i] = heads[icell];
       heads[icell]=i;

	}

	/* Neighbor evaluation for fluid particle */

	for(int i=0;i<Nf;i++)
	{
             tempnode=(struct neighlist*)malloc(sizeof(struct neighlist));
             (fp+i)->neighs=tempnode;
             tempnode->next=NULL;
             tempnode->index=-1;
             xp=(fp+i)->x[0];
             yp=(fp+i)->x[1];

//printf("part is %d\t",i);
    for(ncell=0;ncell<totneigh;ncell++)
		{

            neighcell=neigh_calc(ncell);
//printf("neighcell is%d\n",neighcell);

            if(neighcell!=-1)
            {

            add_f_neighs(neighcell,i);
            add_w_neighs(neighcell,i);
            add_s_neighs(neighcell,i);

		 }
//printf("%d\n",ncell);
		}

	}

	/*Neighbor evaluation for wall particle*/
     for(int i=0;i<Nw;i++)
	{

             tempnode=(struct neighlist*)malloc(sizeof(struct neighlist));
             (wp+i)->neighs=tempnode;
             tempnode->next=NULL;
             tempnode->index=-1;
   	         xp=(wp+i)->x[0];
             yp=(wp+i)->x[1];


    for(ncell=0;ncell<totneigh;ncell++)
		{

            neighcell=neigh_calc(ncell);

            if(neighcell!=-1)
            {

            add_f_neighs(neighcell,i);
            add_w_neighs(neighcell,i);
            add_s_neighs(neighcell,i);

		 }
//printf("%d\n",ncell);
		}

	}

	/*Neighbor evaluation for solid particle*/
     for(int i=0;i<Ns;i++)
	{

             tempnode=(struct neighlist*)malloc(sizeof(struct neighlist));
             (sp+i)->neighs=tempnode;
             tempnode->next=NULL;
             tempnode->index=-1;
   	         xp=(sp+i)->x[0];
             yp=(sp+i)->x[1];


    for(ncell=0;ncell<totneigh;ncell++)
		{

            neighcell=neigh_calc(ncell);

            if(neighcell!=-1)
            {

            add_f_neighs(neighcell,i);
            add_w_neighs(neighcell,i);
            add_s_neighs(neighcell,i);

		 }
//printf("%d\n",ncell);
		}

	}




free(headf);
free(headw);
free(heads);

free(listf);
free(listw);
free(lists);

}
