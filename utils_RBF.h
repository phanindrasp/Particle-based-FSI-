#include <stdio.h>

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED


// Variable definitions

// Neighbor list structure for linked list

struct neighlist
{
        char label;
        int index;
        struct neighlist *next;
};

// Fluid particle structure

struct fluid_particle
{
    float x[2];
    float v[2];
    float rho;
    float P;
    float F[2];
    struct neighlist *neighs;
};

// Solid particle structure

struct solid_particle
{
    float x[2];
    float x0[2];
    float v[2];
    float F[2];
    float rho;
    float P;
    struct neighlist *neighs;
    float m;
    int Nse;
    float sig;
};

// Wall particle structure

struct wall_particle

{
    float x[2];
    float v[2];
    float F[2];
    float rho;
    float P;
    struct neighlist *neighs;
};


// Cell list

struct cell_list

{
    int index;
    char label;
    struct cell_list *link;
};

char *label;
struct neighlist *nodet;
struct neighlist *tempnode;
struct neighlist *tempnode1;
struct neighlist *tempnode2;
struct fluid_particle *fp;
struct wall_particle *wp;
struct solid_particle *sp;
struct cell_list *cell;


int Nf;           // Number of fluid particles
int Nw;           // Number of wall particles
int Ns;           // Number of solid particles
int Ni;           // Number of interface particles
int Na;           // NUmber of attached particle


float Lx;         // Length of the enclosing domain
float Ly;         // Width of the enclosing domain

int Nx;
int Ny;

float dt;         // Time step
float mf;         // Mass of the fluid particle
float msf;         // Mass of the solid particle
float ms;         // Mass of the solid particle
float mu;         // Viscosity of the fluid
float g;          // Acceleration due to gravity

float af,as;
float rx,ry,r,q;  // Distances
float W1,W2;      // Kernel function values
float rc;         // Cut-off radius for interaction
float h;          // Smoothing length
float k;          // Stiffness for the equation of state
float rho0;       // Rest density of fluid
float gam;        // Parameter for the equation of state
float kr;         // Constant for repulsion force
float rco;
float beta,phi;   // Compressible viscosity coefficient
float Dr;         // Dissipation rate

// Parameters for solid

float rhos;       // Density of solid
float c;          // Damping for solid
float E;
float Nu;
float G;
int Ne;        // Number of elements
int Nem;
int temp;
float Area;

float XD,YD,XR,YR,XDh,YDh,XDv,YDv,XRh,YRh,XRv,YRv;
float P,Q,R,S,T,U,V,W;
float EXX,EYY,EXY,ZXX,ZYY,ZXY;
float EXX_X,EXX_Y,EYY_X,EYY_Y,EXY_X,EXY_Y;
float ZXX_X,ZXX_Y,ZYY_X,ZYY_Y,ZXY_X,ZXY_Y;


int **C1;
int **C2;
int **C3;

float S_E;
int *fail;
// GEneral

float xpmax,Lxp,xpmin;
float xmin;
float xmax;
float ymin;
float ymax;
int neighcell;
int icell,ncell,totneigh;
double xc,yc,rd;
double xp,yp;

char filename[200];           // File name
FILE *fptr;
FILE *fptr1;
int counter;

float rvx, rvy;
float DWx1,DWx2,DWy1,DWy2;
float q;

int *headf,*headw,*heads;
int *listf,*listw,*lists;

// Function definitions

void read_points();
void eval_neighs_opt();
void eval_mass();
int neigh_calc(int ncell);
void add_f_neighs(int neighcell,int i);
void add_w_neighs(int neighcell,int i);
void add_s_neighs(int neighcell,int i);
void eval_density();
void simulate_fluid();
void eval_f_force(int i,int j,float rx,float ry,float rvx,float rvy,char lbl);
void simulate_solid();
void update_points();
void write_points(int it);
int DT();
#endif // UTILS_H_INCLUDED
