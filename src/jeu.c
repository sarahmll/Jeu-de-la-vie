#include "../include/jeu.h"

int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}


int compte_voisins_vivants_non_cyclique(int i, int j, grille g) {
  int v = 0,l=g.nbl, c = g.nbc;
 
  int nbi=(i-1>=0 ? i-1 : 0);
  
  while( nbi <= i+1 && nbi < l ){
	  int nbj=(j-1>=0 ? j-1 : 0);
	  while( nbj <= j+1 && nbj < c ){
		  if (!( nbi == i && nbj == j)) v+=est_vivante(nbi,nbj,g);
		  nbj++;
	  }
	  nbi++;
  }
  return v;
}


void evolue (grille *g, grille *gc, int (*compte_voisins_vivants)(int,int,grille), int vieillissement){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			
			if(!est_non_viable(i,j,*gc))
			{
				v = compte_voisins_vivants(i, j, *gc);
				if (est_vivante(i,j,*g)) 
				{ // évolution d'une cellule vivante
					if(vieillissement==0)
					{
						
						if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
						
						if(est_vivante(i,j,*g)) set_vivante(i,j,*g);
					}
					else
					{
						if(g->cellules[i][j]<=8)
						{
							if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
						
							if (est_vivante(i,j,*g)) vieillit(i,j,*g);
						}
						else
						{
							set_morte(i,j,*g);
						}
					}
				}
				else 
				{
					if(vieillissement==0)
					{
						if ( v==3 ) set_vivante(i,j,*g);
						
						if(est_vivante(i,j,*g)) set_vivante(i,j,*g);
					}
					else
					{
						if ( v==3 ) set_vivante(i,j,*g);
						
						if (est_vivante(i,j,*g)) vieillit(i,j,*g);
					}
				}
			}
		}
	}
	return;
}
