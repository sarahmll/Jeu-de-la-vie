
#include "../include/io.h"


#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <string.h>

int taille1 = (taille_fenetre/40);
int taille2 = taille_fenetre/65;

int text_perimetre = taille_fenetre/7;


int nbre_evolution = 0;


char temp[5];


char varChar[256];


int vieillissement = 0;


int oscillation;


int (*compte_voisins_vivants)(int,int,grille) = compte_voisins_vivants_cyclique;


char new_grille[255];


int nv = 0;




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


int grilles_identiques(grille ga, grille gb) {
	if (ga.nbc != gb.nbc || ga.nbl != gb.nbl) {
		return 0;
	}

	for (int i = 0; i < ga.nbl; i++) {
		for (int j = 0; j < gb.nbc; j++) {
			if (est_vivante(i, j, ga) != est_vivante(i, j, gb)) {
				return 0;
			}
		}
	}
	
	return 1;
}

int colonie_oscillante(grille g) 
{
	int limite_max = 200;
	grille gc, gtemp;
	alloue_grille(g.nbl, g.nbc, &gc);
	alloue_grille(g.nbl, g.nbc, &gtemp);
	copie_grille(g, gc);
	int i;
	for (i = 0; i < limite_max; i++) {
		evolue(&gc, &gtemp, compte_voisins_vivants, vieillissement);
		if (grilles_identiques(g, gc)) {
			libere_grille(&gc);
			libere_grille(&gtemp);
			break;
		}
	}
	
	return (i==limite_max)?(-1):(i+1);
}


int colonie_oscillante2(grille g)
{
	int limite_max = 100;
	
	grille bufferGrille[limite_max];
	grille gc, gtemp;
	alloue_grille(g.nbl, g.nbc, &gc);
	alloue_grille(g.nbl, g.nbc, &gtemp);
	copie_grille(g, gc);
	
	int i, j;
	for(i=0; i<limite_max; i++) {
		if(grille_vide(gc)) return -1;
		alloue_grille(g.nbl, g.nbc, &bufferGrille[i]);
		copie_grille(gc, bufferGrille[i]);
		evolue(&gc, &gtemp, compte_voisins_vivants, vieillissement);
		for(j=0; j<i; j++) {
			if (grilles_identiques(bufferGrille[j], gc) == 1){
				return i+1;}
		}
	}
	return (i==limite_max)?(-1):(i+1);
}




void affiche_grille_graphique(cairo_surface_t *surface, grille g)
{
	cairo_t *cr;
	cr=cairo_create(surface);
	
	
	cairo_set_source_rgb (cr, 0.1, 0.3, 0.6);
	cairo_paint(cr);
	
	cairo_select_font_face (cr, "Ubuntu", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (cr, taille1);
	
	
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_move_to(cr, 0, taille1);
	sprintf(temp, "%d", nbre_evolution);
	strcpy(varChar, "Temps d'évolution : ");
	cairo_show_text(cr, strcat(varChar, temp));
	
	cairo_move_to(cr, 0, 5*taille1);
	if(vieillissement == 1) cairo_show_text(cr, "vieillissement activé");
	else cairo_show_text(cr, "vieillissement désactivé");
	
	cairo_move_to(cr, 650, taille1);
	if(compte_voisins_vivants==compte_voisins_vivants_cyclique) cairo_show_text(cr, "mode cyclique activé");
	else cairo_show_text(cr, "mode cyclique désactivé");
	cairo_move_to(cr, 650, 5*taille1);
	
	if (oscillation>=0){
		sprintf(varChar, "Oscillation dans : %d évolutions", oscillation);
		cairo_move_to(cr, 650, 5*taille1);
		cairo_show_text(cr, varChar);
	}
	else
	{
		sprintf(varChar, "pas d'oscillation");
		cairo_move_to(cr, 650, 5*taille1);
		cairo_show_text(cr, varChar);
	}
	
	cairo_rectangle(cr,13*taille1,taille_fenetre/25,12*taille1,3*taille1);
	(cairo_set_source_rgb(cr, 0, 0, 0));
	cairo_fill(cr);
	cairo_stroke(cr);
	
	(cairo_set_source_rgb(cr, 1, 0, 0));
	cairo_move_to(cr, 13*taille1, taille1);
	cairo_show_text(cr, "grille suivante :");
	cairo_move_to(cr, 13*taille1,3*taille1);
	cairo_select_font_face (cr, "Courrier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_show_text(cr, new_grille);
	
	
	
	
	
	cairo_rectangle(cr,200,650,80,80);
	
	cairo_set_source_rgb(cr, 0.9, 0.4, 0.9);
	cairo_fill(cr);
	cairo_stroke(cr);
	cairo_rectangle(cr,600,650,80,80);
	
	cairo_set_source_rgb(cr, 1.0, 1.0, 0.4);
	cairo_fill(cr);
	cairo_stroke(cr);
	cairo_set_source_rgb(cr, 0.9, 0.4, 0.9);
	cairo_move_to(cr, 200,630);
	cairo_show_text(cr, "viable ");
	cairo_set_source_rgb(cr, 1.0, 1.0, 0.4);
	cairo_move_to(cr, 580,630);
	cairo_show_text(cr, " non viable ");
	
	for(int li = 0; li < g.nbl; li++) { 
		for(int co = 0; co < g.nbc; co++) { 	
			
			cairo_set_source_rgb (cr, 1, 1, 1); 
				
			cairo_rectangle(cr,co*longueur,li*largeur+text_perimetre,longueur,largeur); 
			
			for(int dec = 1; dec<=8; dec++) { 
				if(g.cellules[li][co] ==dec ){
				cairo_set_source_rgb (cr, 0.9, 0.4, 0.9); 
				cairo_fill(cr);}
			}
			
			if(g.cellules[li][co] == -1) { 
				cairo_set_source_rgb (cr, 1.0, 1.0, 0.4); 
				cairo_fill(cr);
			}
			
			cairo_stroke(cr);

		}
	}
	
	
	
	cairo_destroy(cr);	
}


void debut_jeu(grille *g, grille *gc){
	
	
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	
	
	longueur = (double)(taille_fenetre)/((g->nbc));
	largeur = (double)(taille_fenetre-text_perimetre)/(((g->nbl)*2));
	
	
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, taille_fenetre, taille_fenetre, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "Jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask|KeyReleaseMask);
	XMapWindow(dpy, win);
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), taille_fenetre, taille_fenetre);


	while(1) {
		
		XNextEvent(dpy, &e);
		
		
		
		if(e.type==Expose && e.xexpose.count<1) 
		{
			affiche_grille_graphique(cs, *g);
		}
		
		
		else if(e.type==ButtonPress && e.xbutton.button == 1) 
		{
			evolue(g,gc, compte_voisins_vivants, vieillissement);
			nbre_evolution++;
			affiche_grille_graphique(cs, *g);
		}
		
		
		if(e.type==KeyPress && e.xkey.keycode==54) 
		{
		(compte_voisins_vivants == compte_voisins_vivants_cyclique)?(compte_voisins_vivants =       		   			compte_voisins_vivants_non_cyclique):(compte_voisins_vivants =                                   

		compte_voisins_vivants_cyclique);                                    
			affiche_grille_graphique(cs, *g);
		}
		
		if(e.type==KeyPress && e.xkey.keycode==55) 
		{
			(vieillissement==1)?(vieillissement=0):(vieillissement=1);
			affiche_grille_graphique(cs, *g);
		}
		
		

		if(e.type==KeyPress && e.xkey.keycode==32) 
		{
		oscillation = colonie_oscillante2(*g);
		affiche_grille_graphique(cs, *g);
		}
		
		if(e.type==KeyPress && e.xkey.keycode==57) 
		{
			KeySym key;			
			char carac[256];
			nv = 1;
			while(1)
			{
				XNextEvent(dpy, &e);
							if (e.type==KeyPress && XLookupString(&e.xkey,carac,256,&key,0)==1) 
							{
								if(e.xkey.keycode == 36) 
								{
									nv=0;
					                libere_grille(g);
					                libere_grille(gc);
									init_grille_from_file(new_grille, g);
									alloue_grille(g->nbl, g->nbc, gc);
									longueur = taille_fenetre/((g->nbc));
									largeur = (taille_fenetre-text_perimetre)/(((g->nbl)*2));
									nbre_evolution = 0;
									oscillation = 0;
									affiche_grille_graphique(cs, *g);
									break;
								}
								else if (e.xkey.keycode == 22) 
								{
									new_grille[strlen(new_grille)-1] = '\0'; 
								}
								else if (e.xkey.keycode == 9) 
								{
									nv=0; 
									affiche_grille_graphique(cs, *g);
									break;
								}

								else
								{
									strcat(new_grille, carac);
								}
							}
							affiche_grille_graphique(cs, *g);
			}

		}
		
		
		if (e.type==ButtonPress && e.xbutton.button == 3)
			break;
		
	}
	
	cairo_surface_destroy(cs); 
	XCloseDisplay(dpy); 
	
	return;	
}
