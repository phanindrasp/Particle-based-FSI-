#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils_RBF.h"


void write_points(int it)
{

/* Open the file to be written */

sprintf(filename,"/home/user/Documents/Phani/PFSI_paper1/data/points%d.csv",it);
//sprintf(filename,"/home/user/Documents/Phani/PFSI_paper1/Parametric_study/1/points%d.csv",it);

//sprintf(filename, "C:/Users/Phani/Documents/Phani_research/6. Entropy production+fluid structure/Particle-based fluid codes/SPH/SPH_RBF/data/DBS/points%d.csv", it);
fptr = fopen(filename, "w"); // "w" defines "writing mode"


for (int i=0;i<Nf;i++)
{
    fprintf(fptr, "%f,%f,%f,%f,f\n",(fp+i)->x[0],(fp+i)->x[1],(fp+i)->v[0],(fp+i)->P);

}

for (int i=0;i<Nw;i++)
{
    fprintf(fptr, "%f,%f,%f,%f,w\n",(wp+i)->x[0],(wp+i)->x[1],(wp+i)->v[0],(wp+i)->v[1]);

}

for (int i=0;i<Ns;i++)
{
    fprintf(fptr, "%f,%f,%f,%f,s\n",(sp+i)->x[0],(sp+i)->x[1],(sp+i)->v[0],(sp+i)->sig);

}
/*
for (int i=0;i<Ne;i++)
{
  fprintf(fptr, "%d\n",fail[i]);
}
*/
    fclose(fptr);
}
