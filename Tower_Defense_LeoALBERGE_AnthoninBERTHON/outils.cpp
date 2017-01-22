#include "outils.h"

bool est_dans_rectangle(IntPoint2 p, IntPoint2 coin_gauche,int w, int h){
    if( p.x()< coin_gauche.x()+w && p.x()> coin_gauche.x() && p.y()< coin_gauche.y()+h && p.y()> coin_gauche.y())
        return true;
    return false;
}


float distance(IntPoint2 p1, IntPoint2 p2) {
    return sqrt(pow(p1[0]-p2[0],2)+pow(p1[1]-p2[1],2));
}

void aligne_grille(IntPoint2& p) {
    p.x()=longueur_case*((p.x()/longueur_case)+1)-longueur_case/2;
    p.y()=longueur_case*((p.y()/longueur_case)+1)-longueur_case/2;
}


IntPoint2 centre(IntPoint2 p, int width, int height) {
    IntPoint2 c= IntPoint2((2*p[0]+width)*longueur_case/2, (2*p[1]+height)*longueur_case/2);
    return c;
}


IntPoint2 grille_coord(IntPoint2 p) {
    div_t dx= div(p[0], longueur_case);
    div_t dy= div(p[1], longueur_case);
    return IntPoint2(dx.quot, dy.quot);
}


void InitRandom() {
    srand((unsigned int)time(0));
}

int random_int(int a, int b) {
    return rand()%(b-a) +a;
}
