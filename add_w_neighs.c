#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils_RBF.h"


void add_w_neighs(int neighcell,int i)
{

int j;

            j=headw[neighcell];

			while(j!=-1)
			{

                          xc = (xp-((wp+j)->x[0]));
			  yc = (yp-((wp+j)->x[1]));


                       rd=sqrt(pow(xc,2)+pow(yc,2));


	               if(rd<rc && j!=i)
	                {

                     tempnode->index=j;
                     tempnode->label='w';
                     nodet=(struct neighlist*)malloc(sizeof(struct neighlist));
                     tempnode->next=nodet;
                     tempnode=nodet;
                     tempnode->next=NULL;
                     tempnode->index=-1;

                      }

j=listw[j];


 			}

}

