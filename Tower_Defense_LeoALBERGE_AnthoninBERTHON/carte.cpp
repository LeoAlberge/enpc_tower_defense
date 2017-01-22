#include "carte.h"




Carte::Carte(char nom) {
     loadColorImage(srcPath("herbe.png"), texture_byte, wh, hh);
     switch(nom) {

     case 'c':
         longueur=2160;
         largeur=longueur_case*2;
         chemin=new IntPoint2[longueur];

         for (int i=0; i<100; i++)  {
             chemin[i][0]=width_fenetre-100;
             chemin[i][1]=height_fenetre-i;
         }
         for (int i=100; i<500; i++)  {
             chemin[i][0]=width_fenetre-100-i+100;
             chemin[i][1]=height_fenetre-100;
         }
         for (int i=500; i<800; i++)  {
             chemin[i][0]=width_fenetre-500;
             chemin[i][1]=height_fenetre-100-(i-500);
         }
         for (int i=800; i<900; i++)  {
             chemin[i][0]=width_fenetre-500+i-800;
             chemin[i][1]=height_fenetre-400;
         }
         for (int i=900; i<1100; i++)  {
             chemin[i][0]=width_fenetre-400;
             chemin[i][1]=height_fenetre-400+(i-900);
         }
         for (int i=1100; i<1360; i++)  {
             chemin[i][0]=width_fenetre-400+i-1100;
             chemin[i][1]=height_fenetre-200;
         }
         for (int i=1360; i<1500; i++)  {
             chemin[i][0]=width_fenetre-160;
             chemin[i][1]=height_fenetre-200-(i-1360);
         }
         for (int i=1500; i<1600; i++)  {
             chemin[i][0]=width_fenetre-160+(i-1500);
             chemin[i][1]=height_fenetre-340;
         }
         for (int i=1600; i<1740; i++)  {
             chemin[i][0]=width_fenetre-60;
             chemin[i][1]=height_fenetre-340-(i-1600);
         }
         for (int i=1740; i<2000; i++)  {
             chemin[i][0]=width_fenetre-60-(i-1740);
             chemin[i][1]=height_fenetre-480;
         }
         for (int i=2000; i<2120; i++)  {
             chemin[i][0]=width_fenetre-320;
             chemin[i][1]=height_fenetre-480-(i-2000);
         }
         break;

     case 'd':            //Chicane
         longueur=700;
         largeur=longueur_case*2;
         chemin=new IntPoint2[longueur];
         for (int i=0; i<100; i++)  {
             chemin[i][0]=width_fenetre/2;
             chemin[i][1]=height_fenetre-i;
         }
         for (int i=100; i<200; i++)  {
             chemin[i][0]=width_fenetre/2-i+100;
             chemin[i][1]=height_fenetre-100;
         }
         for (int i=200; i<700; i++)  {
             chemin[i][0]=width_fenetre/2-100;
             chemin[i][1]=height_fenetre+100-i;
         }
         break;

     defaut:           //Ligne droite
         longueur=600;
         largeur=longueur_case*2;
         chemin=new IntPoint2[longueur];
         for (int i=0; i<longueur; i++)  {
             chemin[i][0]=width_fenetre/2;
             chemin[i][1]=height_fenetre-i;
         }
         break;
     }
}

const void Carte::affiche() {
    bool ex= false;             //Va permettre de detecter les coins du chemin
    //fillRect(0, 0, width_fenetre, height_fenetre, WHITE);
    putColorImage(IntPoint2(0,0), texture_byte, wh, hh, false, 1.5);


    fillRect(chemin[0]-largeur/2, largeur, 1, ROUGE_CHEMIN);
    for (int i=1; i<longueur; i++) {
        drawPoint(chemin[i], BLACK);
        if(chemin[i-1][1]-chemin[i][1]==0) {            // Cas où le chemin est le long de l'axe des abscisses
            fillRect(chemin[i][0], chemin[i][1]-largeur/2, 1, largeur, ROUGE_CHEMIN);
            if (!ex)
                fillRect(chemin[i-1][0]-largeur/2, chemin[i-1][1]-largeur/2, largeur, largeur, ROUGE_CHEMIN);
            ex= true;
        }
        else {
            fillRect(chemin[i][0]-largeur/2, chemin[i][1], largeur, 1, ROUGE_CHEMIN);
            if (ex)
                fillRect(chemin[i-1][0]-largeur/2, chemin[i-1][1]-largeur/2, largeur, largeur, ROUGE_CHEMIN);
            ex= false;
        }
    }
}

IntPoint2 Carte::getvaleur(int i){
    return chemin[i];
}

int Carte::get_longueur(){
    return longueur;
}

int Carte::get_coordonnee(int i, int j){
    return chemin[i][j];
}

int Carte::get_largeur(){
    return largeur;
}
