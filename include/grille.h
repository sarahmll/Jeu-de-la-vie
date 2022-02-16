/**
 * \file grille.h
 * \brief pour les grilles 
 * \author Lafdhal
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * \struct
 */
// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
typedef struct {
	int nbl;/*!<nombre de lignes */ int nbc; /*!<nombre de colonnes */ int** cellules; /*!<tableau de  tableau */} grille;
 
 /**
 * \fn void alloue_grille (int l, int c, grille* g).
 * \param  l nombre de lignes .
 * \param  c nombre de colonnes .
 * \param *g grille .
 * \brief allocation  et initialisations a 0 les cellules de la grille .
 * \return void.
 */
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);

/**
 * \brief Libère la grille g de la mémoire.
 * \param [in] *g Pointeur sur grille à libérer.
 */
void libere_grille (grille* g);

/**
 * \fn void init_grille_from_file (char * filename, grille* g).
 * \param  *filename le nom du fichier.
 * \param  *g  grille 
 * \brief  fonction  qui prend en arrgument un fichier pour initialiser une grille 
 * \return void.
 */
// alloue et initalise la grille g à partir d'un fichi
void init_grille_from_file (char * filename, grille* g);

/**
 * \fn static inline void set_vivante(int i, int j, grille g).
 * 
 * \param i indice de la ligne .
 * \param j indice de la colonne.
 * \param g grille.
 * \brief f met 1 si sla cellule est vivante .
 * \return void.
 */
// rend vivante la cellule (i,j) de la grille g
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}


/**
 * \fn static inline void vieillit(int i, int j, grille g){g.cellules[i][j]++;}
 * \param [in] i Ligne de la cellule à vieillir
 * \param [in] j Colonne de la cellule à vieillir
 * \param [in] g Grille à considérer
 */
static inline void vieillit(int i, int j, grille g){g.cellules[i][j]++;}

/**
 * \fn static inline void set_morte(int i, int j, grille g).
 * \param  i indice de la ligne .
 * \param  j indice de la colonne .
 * \param  g grille.
 * \brief  met 0 si la cellue est morte.
 * \return void.
 */
// rend morte la cellule (i,j) de la grille g
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}


static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;}


static inline int est_non_viable(int i, int j, grille g){return (g.cellules[i][j] == -1);}

/**
 * \fn static inline int est_vivante(int i, int j, grille g).
 * \param i indice de la ligne de la cellule.
 * \param j indice de la colonne de la cellule.
 * \param g grille.
 * \brief test si la cellules  est morte ou vivante 
 * \return renvoie 0 si cellules est morte .
 */
// teste si la cellule (i,j) de la grille g est vivante
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] > 0;}

/**
 * \fn void copie_grille (grille gs, grille gd).
 * \param gs grille  .
 * \param gd grille .
 * \brief  copie la grille .
 * \return void.
 */
// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

#endif
