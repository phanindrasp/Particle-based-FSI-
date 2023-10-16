#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "utils_RBF.h"


int neigh_calc(int ncell)
{
    	/*Finding neighbour cells (No periodic BCs)*/

	switch(ncell)
   	{
  	  case 0:
  	    if (floor(Ny*(yp-ymin)/Ly)==0)
        {
            neighcell=-1;

        }
        else if (floor(Nx*(xp-xmin)/Lx)==0)
        {
            neighcell=Nx*floor(Ny*(yp-ymin)/Ly)-1;

        }
        else
        {

            neighcell=floor(Nx*(xp-xmin)/Lx-1)+Nx*floor(Ny*(yp-ymin)/Ly-1);

        }

      	break;
   	  case 1:
   	     if (floor(Ny*(yp-ymin)/Ly)==0)
        {
            neighcell=-1;
        }
        else
        {
	     	neighcell=floor(Nx*(xp-xmin)/Lx)+Nx*floor(Ny*(yp-ymin)/Ly-1);
        }
      	break;
      case 2:
		 if (floor(Ny*(yp-ymin)/Ly)==0)
        {
            neighcell=-1;
        }
        else if (floor(Nx*(xp-xmin)/Lx)==Nx-1)
        {
            neighcell=Nx*floor(Ny*(yp-ymin)/Ly)-Nx;
        }
        else
        {
		    neighcell=floor(Nx*(xp-xmin)/Lx+1)+Nx*floor(Ny*(yp-ymin)/Ly-1);
        }
      	break;
      case 3:
        if (floor(Nx*(xp-xmin)/Lx)==0)
        {
            neighcell=Nx*floor(Ny*(yp-ymin)/Ly)-1;

        }
        else
        {
		neighcell=floor(Nx*(xp-xmin)/Lx-1)+Nx*floor(Ny*(yp-ymin)/Ly);

        }
      	break;
      case 4:
        neighcell=floor(Nx*(xp-xmin)/Lx)+Nx*floor(Ny*(yp-ymin)/Ly);
      	break;
      case 5:
         if (floor(Nx*(xp-xmin)/Lx)==Nx-1)
        {

            neighcell=Nx*floor(Ny*(yp-ymin)/Ly);
        }
        else
        {

		neighcell=floor(Nx*(xp-xmin)/Lx+1)+Nx*floor(Ny*(yp-ymin)/Ly);
        }
      	break;
      case 6:
         if (floor(Ny*(yp-ymin)/Ly)==Ny-1)
        {
            neighcell=-1;
        }
        else if (floor(Nx*(xp-xmin)/Lx)==0)
        {
            neighcell=Nx*floor(Ny*(yp-ymin)/Ly)+2*Nx-1;
        }
        else
        {
		neighcell=floor(Nx*(xp-xmin)/Lx-1)+Nx*floor(Ny*(yp-ymin)/Ly+1);
        }
      	break;
      case 7:
         if (floor(Ny*(yp-ymin)/Ly)==Ny-1)
        {
            neighcell=-1;
        }
        else
        {
		neighcell=floor(Nx*(xp-xmin)/Lx)+Nx*floor(Ny*(yp-ymin)/Ly+1);
        }
     	break;
      case 8:
           if ( floor(Ny*(yp-ymin)/Ly)==Ny-1)
        {
            neighcell=-1;
        }
        else if (floor(Nx*(xp-xmin)/Lx)==Nx-1)
        {
            neighcell=Nx*floor(Ny*(yp-ymin)/Ly)+Nx;

        }
        else
        {
		neighcell=floor(Nx*(xp-xmin)/Lx+1)+Nx*floor(Ny*(yp-ymin)/Ly+1);
        }

        break;
   	}

   	return neighcell;
}
