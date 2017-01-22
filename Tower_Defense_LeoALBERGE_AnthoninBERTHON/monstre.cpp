#include "monstre.h"

Monstre::Monstre(int vitesseinitiale, int point_de_vie_initial, int t, int but, Carte c){
    if (point_de_vie_initial>200)
        loadAlphaColorImage(srcPath("monstre_jaune.png"), image, w_image, h_image);
    else
        loadAlphaColorImage(srcPath("monstre_violet.png"), image, w_image, h_image);

    taille= t;
    vitesse=vitesseinitiale;
    point_de_vie=point_de_vie_initial;
    point_de_vie_max=point_de_vie_initial;
    position= c.getvaleur(0)-taille/2;
    position[1]+=20;
    //position[0]+= random_int(-(c.largeur/2), c.largeur/2);
    position_chemin=0;
    mort= false;
    butin= but;
}

int Monstre::get_taille(){
    return taille;
}
bool Monstre::get_mort(){
    return mort;
}

bool Monstre::hit(int degat){
    point_de_vie-=degat;
    if (point_de_vie<=0) {
        mort=true;
        return true;
    }
    else
        return false;
}



void Monstre::nouvelle_position(Carte c){
    position_chemin+=vitesse;
    IntPoint2 pos=c.getvaleur(position_chemin);
    position[0]=pos[0]-taille/2;
    position[1]=pos[1]-taille/2;

}



IntPoint2 Monstre::get_position() {
    return IntPoint2(position.x()+taille/2, position.y()+taille/2);
}


void const Monstre::affiche(){

    putAlphaColorImage(position.x(), position.y(), image, w_image, h_image, false, taille/float(w_image));
    drawLine(position.x(),position.y()-3, position.x()+ taille,position.y()-3, BLACK, 3);
    drawLine(position.x(),position.y()-3, position.x()+ (taille*point_de_vie/point_de_vie_max),position.y()-3, GREEN, 3);
}





