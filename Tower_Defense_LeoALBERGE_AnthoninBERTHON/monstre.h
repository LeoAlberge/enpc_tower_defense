#pragma once

#include "carte.h"




class Monstre {
    int w_image, h_image;
    AlphaColor* image;
    int position_chemin;
    int vitesse ;
    int point_de_vie;
    int point_de_vie_max;
    int butin;
    IntPoint2 position;
    int taille;
    bool mort;
public:

    Monstre(int vitesseinitiale, int point_de_vie_initial, int t, int but, Carte c);    //ok pour l'idee qu'on suit le chemin en se deplacant de vitesse cases sur le chemin
    void const affiche();// a reflechir
    void nouvelle_direction(Carte c);// a voir si on part sur la premiere idee
    void nouvelle_position(Carte c);// fait
    bool hit(int degat);//simple et fait
    IntPoint2 get_position();//retourne le vecteur position du monstre
    int get_taille();
    bool get_mort();


};



