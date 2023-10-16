#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void main()
{

float temp1,temp2;
char lbl;
FILE *fptr,*fptr1;

//fptr=fopen("/home/user/Documents/Phani/PFSI_paper1/data/points.csv","r");
//fptr1=fopen("/home/user/Documents/Phani/PFSI_paper1/data/points_nodes.txt","w");

fptr=fopen("/home/user/Documents/Phani/PFSI_paper1/Parametric_study/1/points.csv","r");
fptr1=fopen("/home/user/Documents/Phani/PFSI_paper1/Parametric_study/1/points_nodes.txt","w");

while(fscanf(fptr,"%f,%f,%c",&temp1,&temp2,&lbl)!=EOF)
 {

    if(lbl=='s')
     {

        fprintf(fptr1,"%f %f\n",temp1,temp2);

     }

 }

fclose(fptr);
fclose(fptr1);


}












