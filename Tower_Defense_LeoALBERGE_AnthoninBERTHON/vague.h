#pragma once
#include <iostream>
#include "monstre.h"
#include "tour.h"

using namespace std;

const int nombre_max_monstres= 100;
const int nombre_max_tours= 100;


class Vague {
    bool vie_en_moins;
    int argent_en_plus;
    int latence;
    int manche;
    int nombre_monstres;
    int nombre_tours;
    vector<Monstre> tableau_monstres;
    vector<Tour> tableau_tours;

public:

    Vague();
    void mort_monstre(int k);
    void mort_tour(int k,int prix_vente);//Mort du ieme element du tableau_monstre
    void nouvelle_manche(Carte c);
    void nouvelles_positions(Carte c);
    void affiche();
    void nouvelle_tour(Tour T);
    void check_mort();                  //Regarde s'il a des monstres morts
    void boucle_principale(Carte c);
    bool vague_finie();
    void fin_chemin();
    int get_nombre_tours();
    int get_latence();
    int get_manche();
    int get_argent_en_plus();
    bool get_vie_en_moins();
    void set_vie_en_moins( bool a);
    void set_argent_en_plus(int a);
    Tour get_tour(int numero);
};

