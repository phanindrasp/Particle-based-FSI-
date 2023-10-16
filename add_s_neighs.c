#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils_RBF.h"


void add_s_neighs(int neighcell,int i)
{

int j;

            j=heads[neighcell];

			while(j!=-1)
			{

              xc = (xp-((sp+j)->x[0]));
	      yc = (yp-((sp+j)->x[1]));


                       rd=sqrt(pow(xc,2)+pow(yc,2));


	               if(rd<rc && j!=i)
	                {
//printf("%d %d %f\n",i,j,rd);
                     tempnode->index=j;
                     tempnode->label='s';
                     nodet=(struct neighlist*)malloc(sizeof(struct neighlist));
                     tempnode->next=nodet;
                     tempnode=nodet;
                     tempnode->next=NULL;
                     tempnode->index=-1;

                      }

j=lists[j];


 			}

}

