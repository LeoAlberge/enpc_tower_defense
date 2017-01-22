#pragma once

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include"tour.h"
#include "vague.h"


using namespace Imagine;
const int nombre_tour=2;
const int height_menu=100;

class Tour;
class Vague;


class Rectangle {
public:
    int x, y, w, h;
    Color col;
    bool plein;
    int prix;
    Rectangle();
    Rectangle(int x0, int y0, int w0, int h0, bool plein0, int p, Color col0=BLACK);
    Rectangle(IntPoint2 p1, IntPoint2 p2, bool plein0, Color col0=BLACK);
    bool est_dedans(int xc, int yc);
    void affiche();
};



class Menu {
    //Tour tour(IntPoint2(0,0),20,52,50);
    bool clique_actif_tour;
    IntPoint2  position_tour_a_vendre;
    int numero_tour_a_vendre;
    int vague_actuelle;
    int vie;
    int latence;
    bool clique_actif;
    bool depot_tour;
    int tour_mobile;            //-1 si aucune tour n'est entrain d'etre placee, 0-3 sinon (num de la tour)
    IntPoint2 mouse_motion;
    Rectangle R[4];             //Vignettes contenant les tours disponibles, vont recevoir les clicks de l'utilisateur lors de la creation d'une tour.
    Tour T[4];
    int latence_affichage;
    int argent;
public:

    Menu(int argent_intinial, int vie_initial);
    const void affiche();
    void affiche_dynamique();
    void affiche_tour_dynamique();
    void drag_n_drop(Vague &V, Carte C, Event e);
    Tour creation_tour(/*IntPoint2 position*/);
    void affiche_grille();
    void perd_vie(Vague& V);
    void gagne_argent(Vague& V);
    bool fin_de_partie();
    int get_latence(Vague V);
    bool est_sur_chemin(IntPoint2 position, Carte C);
    void vendre_tour(Event e, Vague &V);
    int h_valider;
    int w_valider;
    byte *valider;
};



