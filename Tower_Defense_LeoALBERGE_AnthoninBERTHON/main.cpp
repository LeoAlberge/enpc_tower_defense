#include <iostream>
#include <chrono>
#include "Imagine/Graphics.h"
#include "Imagine/Common.h"

#include "tour.h"
#include "menu.h"
#include "vague.h"



using namespace Imagine;
using namespace std;




//Rectangle groupe_rectangle[4]={Rectangle(30+1*90, height_fenetre+20, 60, 60, false),
//                               Rectangle(30+2*90, height_fenetre+20, 60, 60, false),
//                               Rectangle(30+3*90, height_fenetre+20, 60, 60, false),
//                               Rectangle(30+4*90, height_fenetre+20, 60, 60, false)};


bool get_click_constant(IntPoint2& p) {
    Event e;
    getEvent(frame_rate, e);
    if (e.button==1 && e.type==EVT_BUT_ON) {
        p=e.pix;
        cout << p[0] << " " << p[1] << endl;
        return true;
    }
    else
        return false;
}





int main() {
    InitRandom();
    openWindow(width_fenetre, height_fenetre+height_menu);
//    AlphaColor * texture;
//    int hh,wh;
//    bool charge=loadAlphaColorImage(srcPath("herbe.png"), texture, wh, hh);

//    if(!charge) {
//        std::cout << "Echec de lecture d'image" << std::endl;
//    }
    Carte c('c');
    c.affiche();


    //Test Tour
    IntPoint2 p;
    p[1]=height_fenetre/2;
    p[0]=width_fenetre/2-30;
    //Tour T(p, 50, 40, 6);
    //T.affiche();


//    //Test Monstre
//    Monstre M(2, 100, c);
//    M.affiche();
//    Monstre M_tab[1]={M};

    //Test Vague
    Vague V;
    V.nouvelle_manche(c);

    //Test Menu
    Menu Me(100, 20);
    Rectangle R(30, height_fenetre+20, 60, 60, 0, false);
    R.affiche();


    //Test affichage + shoot
    Event e;
    std::chrono::time_point<std::chrono::system_clock>  time_origine,time_origine2, checkpoint, avant, apres;

    time_origine= std::chrono::system_clock::now();
    time_origine2=std::chrono::system_clock::now();
    int arret=0;

    while(!Me.fin_de_partie() /*&& arret<10000*/) {

        checkpoint= std::chrono::system_clock::now();
        int temps= std::chrono::duration_cast<std::chrono::milliseconds>(checkpoint-time_origine).count();

        arret=std::chrono::duration_cast<std::chrono::milliseconds>(checkpoint-time_origine2).count();
        getEvent(1, e);
        noRefreshBegin();

        //Affiche monstre, tour, carte, recherche ennemie+tir des tours, check mort
        if (temps>42) {
            V.boucle_principale(c);
            time_origine= checkpoint;
        }
        Me.drag_n_drop(V, c, e);
        Me.vendre_tour(e,V);
//        if(Me.clique_actif)
//            cout<<"true"<<endl;
//        else
//            cout<<"false"<<endl;

        Me.affiche();
        noRefreshEnd();


    }
    endGraphics();
    return 0;
}

