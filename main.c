#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils_RBF.h"


void main()
{

dt=1e-5;                // Time step (LDC)
//dt=1e-5;              // Time step (DBS)
float T=1;              // Simulation time (LDC)
//float T=1;            // Simulation time (DBS)
int Nt=T/dt;            // Total number of time steps

mu=1;                // Viscosity of the fluid (LDC)
//mu=0.1;               // Viscosity of the fluid (DBS)
//mu=0.05;
kr=10;
g=9.81;                 // Acceleration due to gravity
k=1e4;                  // Compressibility (LDC)
//k=1e4;                // Compressibility (DBS)
                         
rho0=1000;
rhos=2500;

counter=0;

c=0;
E=1e7;
Nu=0.3;
G=E/(2*(Nu+1));
Ne=0;
gam=7;
beta=0;

    read_points();


    eval_mass();


for (int i=0;i<Nt;i++)
{

    printf("Time step is %d\n",i);

// Write positions of particles into a file

if(i%1000==0)
 {

    write_points(i);
}

// Evaluate neighbors
    eval_neighs_opt();
 
// Simulate the fluid

    simulate_fluid();
   
// Simulate the solid

    simulate_solid();
   
// Update positions of particles
   
     update_points();
  
}


}
