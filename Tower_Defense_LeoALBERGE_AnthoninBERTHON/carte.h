#pragma once

#include "outils.h"
#include<Imagine/Images.h>

//Classe de la carte, permet de la creer, de gerer le chemin des monstres et de l'afficher

class Carte {
    int wh; //Permet de stocker l'image et ses dimensions
    int hh;
    byte* texture_byte;
    int longueur;
    int largeur;
    IntPoint2* chemin; //stocke le chemin comme une suite de pixel
public:

    Carte(char nom); //constructeur, le char est un parametre qui change la carte
    const void affiche();
    IntPoint2 getvaleur(int i);
    int get_longueur();
    int get_coordonnee(int i, int j);
    int get_largeur();


};
