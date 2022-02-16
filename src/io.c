

#include "../include/io.h"


int temps_evolution = 0;


int vieillissement = 0;


int (*compte_voisins_vivants)(int,int,grille) = compte_voisins_vivants_cyclique;


int oscillation;

int grille_vide(grille g){
	int l = g.nbl, c=g.nbc, i, j;
	for(i = 0; i < l; i++) {
		for(j=0; j<c; j++) {
			if(g.cellules[i][j] > 0)
				return 0;
		}
	}
	
	return 1;
}

int grilles_identiques(grille grille1, grille grille2) {
	if (grille1.nbc != grille2.nbc || grille1.nbl != grille2.nbl) {
		return 0;
	}

	for (int i = 0; i < grille1.nbl; i++) {
		for (int j = 0; j < grille2.nbc; j++) {
			if (est_vivante(i, j, grille1) != est_vivante(i, j, grille2)) {
				return 0;
			}
		}
	}
	return 1;
}


int colonie_oscillante(grille g) 
{
	int oscillation_maximum = 200;
	grille gc, grille_veri;
	alloue_grille(g.nbl, g.nbc, &gc);
	alloue_grille(g.nbl, g.nbc, &grille_veri);
	copie_grille(g, gc);
	int i;
	for (i = 0; i < oscillation_maximum; i++) {
		evolue(&gc, &grille_veri, compte_voisins_vivants, vieillissement);
		if (grilles_identiques(g, gc)) {
			libere_grille(&gc);
			libere_grille(&grille_veri);
			break;
		}
	}
	
	return (i==oscillation_maximum)?(-1):(i+1);
}


int colonie_oscillante2(grille g)
{
	int oscillation_maximum = 200;
	
	grille grille_fi[oscillation_maximum];
	grille gc, grille_veri;
	alloue_grille(g.nbl, g.nbc, &gc);
	alloue_grille(g.nbl, g.nbc, &grille_veri);
	copie_grille(g, gc);
	
	int i, j;
	for(i=0; i<oscillation_maximum; i++) {
		if(grille_vide(gc)) return -1;
		alloue_grille(g.nbl, g.nbc, &grille_fi[i]);
		copie_grille(gc, grille_fi[i]);
		evolue(&gc, &grille_veri, compte_voisins_vivants, vieillissement);
		for(j=0; j<i; j++) {
			if (grilles_identiques(grille_fi[j], gc) == 1){
				return i+1;
			}
		}
	}
	
	return (i==oscillation_maximum)?(-1):(i+1);
}


void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
	{
		if (ligne[i] == 0 ) printf ("|   "); 
		else 
		{
			if(ligne[i] == -1)
			printf ("| X ");
			else
			printf ("| %d ", ligne[i]-1);
		}
	}
	printf("|\n");
	return;
}

void affiche_grille (grille g){
    
	int i, l=g.nbl, c=g.nbc;
    printf("Temps d'évolution : %d\n", temps_evolution++);
    
    
    if (compte_voisins_vivants==compte_voisins_vivants_cyclique) printf("mode cyclique activé\n");
	else printf("mode cyclique désactivé\n");
    if (vieillissement==1)
    printf("Vieillissement activé \n ");
    else printf("Vieillissement desactivé \n ");
    
   
    if(oscillation!=0) printf("osicillation dans %d\n", oscillation); 
    else 	printf("oscillation\n");
    
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
	printf("\n\x1B[%dA",g.nbl*2 + 10); 
}

void debut_jeu(grille *g, grille *gc){
	
	affiche_grille(*g);
	
	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entrée" pour évoluer
				evolue(g,gc, compte_voisins_vivants, vieillissement);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' :
			{ 
				char newgrille[256];
				printf("entrez la nouvelle grille: ");
				scanf("%s", newgrille);
                efface_grille(*g);
                libere_grille(g);
                libere_grille(gc);
				init_grille_from_file(newgrille, g);
				alloue_grille(g->nbl, g->nbc, gc);
			    system("clear"); 
                temps_evolution = 0;
				affiche_grille(*g);
				temps_evolution = 0;
				oscillation=0;
				break;
                                
                                
			}
            case 'c' :
            { 
				(compte_voisins_vivants == compte_voisins_vivants_cyclique)?(compte_voisins_vivants 			=compte_voisins_vivants_non_cyclique):(compte_voisins_vivants = compte_voisins_vivants_cyclique);
				break;
            }
            case 'v' :
            {
				if (vieillissement==1) (vieillissement=0) ; else (vieillissement=1);
				break;
			}
            case 'o' :
            {
				oscillation = colonie_oscillante2(*g);
				break;
			}
			default : 
			{ 
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
