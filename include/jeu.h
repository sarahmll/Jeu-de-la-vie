/** 
 * \file  jeu.h
 * header pour le déroullement du jeu 
 * \author Lafdhal
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"


// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
/**
 * \fn static inline int modulo(int i, int m).
 * \param  i 
 * \param  m .
 * \brief Fonction qui traite les limites de la grille pour qu'il y aura pa deppasssement de limite
 * \return renvoie le modulo du premier paramétre
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
/**
 * \fn int compte_voisins_vivants_cycliques(int i, int j, grille g).
 * \param i nombre de lignes.
 * \param j nombre de colonnes .
 * \param g une grille.
 * \brief compte le nombre des voisins vivants cyclique.
 * \return renvoie le nombre compter
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g);
/**
 * \fn int compte_voisins_vivants_non_cycliques(int i, int j, grille g).
 * \param i nombre de lignes .
 * \param j nombre de colonnes .
 * \param g une grille
 * \brief   compte le nombre de voisins vivants non cycliques .
 * \return renvoie le nombre compter
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

/**
 * \fn void evolue (grille *g, grille *gc, int (*compte_voisins_vivants)(int,int,grille), int vieillissement);
 * \param *g grille.
 * \param  *gc grille .
 * \param  (*compte_voisins_vivants)(int,int,grille) pérmet a determiner si le mode cyclique est activé ou non 
 * \param  vieillissement pérmet a déterminer si le mode  vieillissement est  activé ou non 
 * \brief    evolue la grille g d'un pas de temps.
 * \return void 
 */
// fait évoluer la grille g d'un pas de temps
void evolue (grille *g, grille *gc, int (*compte_voisins_vivants)(int,int,grille), int vieillissement);

#endif
