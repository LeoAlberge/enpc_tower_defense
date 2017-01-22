#include "vague.h"
#include "menu.h"

Vague::Vague() {
    manche=0;
    Monstre M0(2, 1, 15, 10, Carte('c'));
    Tour T0= Tour(IntPoint2(-100, -100), 10, 10, 10, 10, WHITE);
    vector<Monstre> tab_monstres(nombre_max_monstres, M0);
    vector<Tour> tab_tours(nombre_max_tours, T0);
    tableau_monstres= tab_monstres;
    tableau_tours= tab_tours;
    vie_en_moins= false;
    latence= latence_entre_vague;
}


void Vague::check_mort() {
    for (int i=0; i<nombre_monstres; i++) {
        if (tableau_monstres[i].get_mort()) {
            mort_monstre(i);
        }
    }
}

void Vague::mort_monstre(int k) {
    for (int i=k+1; i<nombre_monstres; i++)
        tableau_monstres[i-1]=tableau_monstres[i];
    nombre_monstres--;
    argent_en_plus+=15;
}
void Vague::mort_tour(int k, int prix_vente){
    for (int i=k+1; i<nombre_tours; i++)
        tableau_tours[i-1]=tableau_tours[i];
    nombre_tours--;
    argent_en_plus+=prix_vente;
}


void Vague::nouvelle_tour(Tour T) {
    nombre_tours++;
    tableau_tours[nombre_tours-1]= T;
}


void Vague::nouvelle_manche(Carte c) {
    manche++;
    switch(manche) {
    case (1):
        nombre_monstres=10;
        nombre_tours=0;
        for (int i=0; i<nombre_monstres; i++) {
            Monstre M(2, 60, 20, 10, c);
            tableau_monstres[i]=M;
        }
        break;
    case (2):
        nombre_monstres=1;
        for (int i=0; i<nombre_monstres; i++) {
            Monstre M(1, 500, 40, 30, c);
            tableau_monstres[i]=M;
        }
        break;
    case (3):
        nombre_monstres=5;
        for (int i=0; i<nombre_monstres; i++) {
            Monstre M(4, 60, 15, 10, c);
            tableau_monstres[i]=M;
        }
        break;
    case (4):
        nombre_monstres=10;
        for (int i=0; i<nombre_monstres; i++) {
            Monstre M(3, 60, 15, 10, c);
            tableau_monstres[i]=M;
        }
        break;
    case (5):
        nombre_monstres=25;
        for (int i=0; i<nombre_monstres; i++) {
            Monstre M(10, 60, 15, 10, c);
            tableau_monstres[i]=M;
        }
        break;
    }
}


void Vague::nouvelles_positions(Carte c) {
    tableau_monstres[0].nouvelle_position(c);
    for (int i=1; i<nombre_monstres; i++) {
        if(!(distance(tableau_monstres[i].get_position(), tableau_monstres[i-1].get_position())<tableau_monstres[i-1].get_taille()*2))
            tableau_monstres[i].nouvelle_position(c);
    }
}

int Vague::get_argent_en_plus(){
    return argent_en_plus;
}
int Vague::get_latence(){
    return latence;
}
int Vague::get_manche(){
    return manche;
}
bool Vague::get_vie_en_moins(){
    return vie_en_moins;
}
int Vague::get_nombre_tours(){
    return nombre_tours;
}

void Vague::affiche() {
    for (int i=0; i<nombre_monstres; i++)
        tableau_monstres[i].affiche();
    for (int i=0; i<nombre_tours; i++)
        tableau_tours[i].affiche();
}
void Vague::set_argent_en_plus(int a){
    argent_en_plus=a;
}
void Vague::set_vie_en_moins(bool a){
    vie_en_moins=a;
}

Tour Vague::get_tour(int numero){
    return tableau_tours[numero];

}

//affiche monstre, tour, carte, actualise les positions, recherche ennemie+tir des tours, check mort
void Vague::boucle_principale(Carte C) {
    C.affiche();
    for (int i=0; i<nombre_monstres; i++)
        tableau_monstres[i].affiche();
    nouvelles_positions(C);
    for (int i=0; i<nombre_tours; i++) {
        tableau_tours[i].affiche();
        int recherche= tableau_tours[i].cherche_ennemie(tableau_monstres, nombre_monstres);
        if (!(recherche==-1)) {
            tableau_tours[i].tir(tableau_monstres[recherche]);
        }
    }
    fin_chemin();
    check_mort();
    if (vague_finie()) {
        latence--;
        if (latence<=0) {
            latence=latence_entre_vague;
            nouvelle_manche(C);
        }
    }
}

bool Vague::vague_finie() {
    return (nombre_monstres==0);
}

void Vague::fin_chemin() {
    for (int i=0; i<nombre_monstres; i++) {
        if (tableau_monstres[i].get_position().y()<1) {
            mort_monstre(i);
            vie_en_moins=true;
        }
    }
}



