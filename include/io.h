/**
 * \file io.h
 * \brief  pour l'affichage !
 * \author LAfdhal
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"


#ifdef GRAPHIQUE 


#define taille_fenetre 1000 


#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <string.h>

double longueur; 

double largeur; 
int grilles_identiques(grille ga, grille gb);

int grille_vide(grille g);
int colonie_oscillante(grille g);
int colonie_oscillante2(grille g);


void affiche_grille_graphique (cairo_surface_t *surface, grille g);


#else

/**
 * \fn void affiche_trait (int c).
 
 * \param c .
 * \brief  affiche un trait horizontal separrant les colonnes .
 * \return void.
 */
// affichage d'un trait horizontal
void affiche_trait (int c);

/**
 * \fn void affiche_ligne (int c, int* ligne).
 * \param c .
 * \param *ligne .
 * \brief   affiche une ligne verticale separrant les lignes .
 * \return void.
 */
// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne);

/**
 * \fn void affiche_grille (grille g).

 * \param g grille .
 * \brief  affiche la grille
 * \return void.
 */
// affichage d'une grille

void affiche_grille (grille g);




/**
 * \fn void efface_grille (grille g).
 
 * \param g grille à effacer.
 * \brief efface la grille 
 * \return void.
 */
// effacement d'une grille
void efface_grille (grille g);

#endif

/**
 * \fn void debut_jeu(grille *g, grille *gc).
 * \param *g  grille.
 * \param *gc  grille.
 * \brief début du  jeu
 * \return void.
 */
// debute le jeu
void debut_jeu(grille *g, grille *gc);
#endif
