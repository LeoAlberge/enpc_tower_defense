#pragma once
#include <vector>
#include <iostream>
#include "monstre.h"



using namespace std;


class Tour {

    int portee;
    int degat;
    int frequence;
    int niveau;
    IntPoint2 orientation;
    bool tir_en_cours;
    IntPoint2 missile;
    int latence;
    int prix;
    Color Col;
    bool port;
    int monstre_en_cours;       //Indice du monstre qui est entrain d'être visé, -1 si pas de monstre à portée
    IntPoint2 position;         //Position de la tour en nombre de case. Passe en public pour l'instant.
public:

    Tour();
    Tour(IntPoint2 position, int portee, int degat, int frequence, int pr, Color c);
    int cherche_ennemie(vector<Monstre> M, int nombre_monstres); //Renvoie l'indice du monstre detecte, -1 si aucun n'est a portee ou si la tour est dans son temps de latence.
    void tir(Monstre &M);
    void amelioration();
    void affiche();
    IntPoint2 get_position();
    int get_prix();
    bool get_port();
    int get_portee();
    void set_port(bool a);
    Color get_color();
    void set_position(IntPoint2 point);

};


