#include "tour.h"
#include "outils.h"

using namespace std;



Tour::Tour() {}


Tour::Tour(IntPoint2 p, int port, int deg, int freq, int pr, Color c) {
    position= p;
    portee= port;
    degat= deg;
    frequence= freq;
    prix= pr;
    niveau=1;
    orientation= 0;
    Col= c;
    tir_en_cours=false;
    monstre_en_cours= -1;
    missile[0]=0; missile[1]=0;
    port= false;
}

int Tour::get_portee(){
    return portee;
}

int Tour::get_prix(){
    return prix;
}

bool Tour::get_port(){
    return port;
}
Color Tour::get_color(){
    return Col;
}
void Tour::set_port(bool a){
    port=a;
}
void Tour::set_position(IntPoint2 point){
    position=point;
}

int Tour::cherche_ennemie(vector<Monstre> M, int nombre_monstres) {
    if (latence==0) {           //On ne cherche un ennemi que si la tour a recupere de son tir precedent.
        float min= pow(width_fenetre,2) + pow(height_fenetre,2); //Equivalent a MAX_INT pour les distances de la fenetre.
        int indice;
        float dist;
        bool shoot=false;       //Dit s'il va falloir tirer ou non.
        if (monstre_en_cours>= nombre_monstres)
            monstre_en_cours= -1;
        if (!(monstre_en_cours==-1)) {
            dist= distance(centre(position), M[monstre_en_cours].get_position());
            if (dist<portee) {
                indice= monstre_en_cours;
                shoot= true;
            }
            else
                monstre_en_cours= -1;
        }

        if (monstre_en_cours==-1) {
            for (int i=0; i<nombre_monstres; i++) {
                dist= distance(centre(position), M[i].get_position());
                if ((dist<portee) && (dist<min) && !(i==monstre_en_cours)) {                  //Parmi les monstres a portee, on veut celui le plus proche de la tour.
                    min=int(dist);
                    indice=i;
                    shoot=true;
                    monstre_en_cours=i;
                }
            }
        }



        if (shoot)
            return indice;
        else
            return -1;
    }
    else {
        latence--;
        return -1;
    }
}


void Tour::tir(Monstre& M) {
    tir_en_cours= true;
    drawLine(centre(position), M.get_position(), Col, 3);
    if (M.hit(degat))
        monstre_en_cours=-1;
    latence=frequence;
}


IntPoint2 Tour::get_position(){
    return position;
}

void Tour::amelioration() {
}


void Tour::affiche() {
    fillRect(position[0]*longueur_case, position[1]*longueur_case, longueur_case, longueur_case, Col);
    drawRect(position[0]*longueur_case, position[1]*longueur_case, longueur_case, longueur_case, GRIS_FONCE);

    if (port)
        drawCircle(centre(position), portee, Col);
}
