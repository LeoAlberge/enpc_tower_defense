#include "menu.h"




Tour tab_T[4]= {Tour(grille_coord(IntPoint2(50, height_fenetre+50)), 60, 10, 10, 15, ORANGE),
                Tour(grille_coord(IntPoint2(50+1*80, height_fenetre+50)) , 40, 20, 13, 30, VIOLET),
                Tour(grille_coord(IntPoint2(50+2*80, height_fenetre+50)), 80, 6, 3, 50, CCYAN),
                Tour(grille_coord(IntPoint2(50+3*80, height_fenetre+50)), 70, 20, 6, 100, GRIS_FONCE)};



Menu::Menu(int argent_intinial, int vie_initial){
    argent=argent_intinial;
    vie=vie_initial;
    loadColorImage(srcPath("valider.png"), valider, w_valider, h_valider);
    latence=0;
    latence_affichage= latence_affichage_init;
    clique_actif_tour=false;
    clique_actif=false;
    mouse_motion=IntPoint2(0,0);
    for (int i=0; i<4; i++) {
        R[i]=Rectangle(20+i*80, height_fenetre+20, 60, 60, false, tab_T[i].get_prix(), BLACK);          //Vignettes contenant les tours disponibles, vont recevoir les clicks de l'utilisateur lors de la creation d'une tour.
        T[i]= tab_T[i];              //4 fois la même tour pour l'instant, on varie plus tard.
    }
    vague_actuelle= 0;
    position_tour_a_vendre= IntPoint2(-1000, 1000);
    numero_tour_a_vendre= -1;
    depot_tour=false;
    tour_mobile= -1;
}

void Menu::vendre_tour(Event e, Vague &V){
    cout << clique_actif_tour << endl;
    if (clique_actif_tour) {
        V.get_tour(numero_tour_a_vendre).set_port(true);
        fillRect(centre(position_tour_a_vendre)+IntPoint2(15,15),100,60,WHITE);
        drawRect(centre(position_tour_a_vendre)+IntPoint2(15,15),100,60,RED);
        Tour t=V.get_tour(numero_tour_a_vendre);
        drawString(centre(position_tour_a_vendre)+IntPoint2(20,30), "Prix de vente " + std::to_string(t.get_prix()/2)+"$" , BLACK, 10);
        drawString(centre(position_tour_a_vendre)+IntPoint2(20,50), "Valider" , BLACK, 10);
        putColorImage(centre(position_tour_a_vendre)+IntPoint2(65,35),valider,w_valider,h_valider,false,1.);


        if (e.type==EVT_BUT_ON) {
            IntPoint2 p=e.pix;
            IntPoint2 position =grille_coord(p);
            if (est_dans_rectangle(p,centre(position_tour_a_vendre)+IntPoint2(65,35),w_valider,h_valider)){
                V.mort_tour(numero_tour_a_vendre,t.get_prix()/2);
                clique_actif_tour=false;
                return;
            }

            for(int i=0; i<V.get_nombre_tours();i++){
                if ( position==V.get_tour(i).get_position()){
                        //V.get_tour(i).port= true;
                        position_tour_a_vendre=position;
                        numero_tour_a_vendre=i;
                        return;
                    }
                }

            clique_actif_tour=false;

            position_tour_a_vendre=IntPoint2(-8000,-8000);
            }

    }

    else {
        V.get_tour(numero_tour_a_vendre).set_port(false);

        if (e.type==EVT_BUT_ON) {
            IntPoint2 p=e.pix;
            IntPoint2 position =grille_coord(p);
            for(int i=0; i<V.get_nombre_tours();i++){

                if ( position==V.get_tour(i).get_position()){
                        clique_actif_tour=true;
                        position_tour_a_vendre=position;
                        numero_tour_a_vendre=i;


                    }

                }



        }

        }
    }


void Menu::drag_n_drop(Vague& V, Carte C, Event e) {
    latence= get_latence(V);                    //On profite de l'argument Vague pour faire le lien entre Menu et Vague
    gagne_argent(V);
    perd_vie(V);
    vague_actuelle= V.get_manche();

    if (clique_actif) {
        if (e.type==EVT_MOTION) {
            if (!(grille_coord(e.pix)==mouse_motion))
                mouse_motion= grille_coord(e.pix);
        }
        if (e.type==EVT_BUT_OFF) {
            clique_actif=false;
            IntPoint2 emplacement_tour= mouse_motion;
            //aligne_grille(emplacement_tour);
            if (!est_sur_chemin(emplacement_tour, C) && (T[tour_mobile].get_prix()<=argent)) {
                Tour new_T= T[tour_mobile];
                new_T.set_position(grille_coord(e.pix));
                V.nouvelle_tour(new_T);
                argent-=new_T.get_prix();
            }

            //if (T[tour_mobile].prix>argent)



            tour_mobile=-1;


        }
    }

    else {
        if (e.type==EVT_BUT_ON) {
            IntPoint2 p=e.pix;
            for (int i=0; i<4; i++) {
                if (R[i].est_dedans(p.x(), p.y())) {
                    clique_actif=true;
                    tour_mobile=i;
                    mouse_motion=grille_coord(e.pix);
                }
            }

        }
    }
}



const void Menu::affiche() {
    drawRect(0, height_fenetre, width_fenetre, height_menu, GREEN, 2);
    fillRect(0, height_fenetre, width_fenetre, height_menu, WHITE);
    drawString(width_fenetre-100, height_fenetre+height_menu/2, std::to_string(vie) + "♥", ROUGE_COEUR, 40);
    drawString(width_fenetre-210, height_fenetre+height_menu/2, std::to_string(argent) + "$", GREEN, 40);
    drawString(width_fenetre-210, height_fenetre+height_menu-20, "Vague: " + std::to_string(vague_actuelle), BLACK, 23);
    if (!(latence==latence_entre_vague)) {
        fillRect(width_fenetre-100, height_fenetre+height_menu-20,
                 80*latence/latence_entre_vague, 10, BLUE);
    }

    for (int i=0; i<4; i++) {
        R[i].affiche();
        T[i].affiche();
    }
    if (clique_actif)
        affiche_dynamique();
}

void Menu::affiche_dynamique() {
    //affiche_grille();
    IntPoint2 c= centre(mouse_motion);

    fillRect(c.x()-longueur_case/2, c.y()-longueur_case/2, longueur_case, longueur_case, T[tour_mobile].get_color());
    drawCircle(c, T[tour_mobile].get_portee(), T[tour_mobile].get_color());
}


void Menu::affiche_grille() {
    Color GRIS_PERLE= Color(206, 206, 206);
    for (int i=0; i<width_fenetre/longueur_case; i++)
        drawLine(i*longueur_case, 0, i*longueur_case, height_fenetre, GRIS_PERLE);
    for (int j=0; j<height_fenetre/longueur_case; j++)
        drawLine(0, j*longueur_case, width_fenetre, j*longueur_case, GRIS_PERLE);
}

void Menu::perd_vie(Vague& V) {
    if (V.get_vie_en_moins()) {
        vie--;
        V.set_vie_en_moins(false);
    }
}


void Menu::gagne_argent(Vague& V) {
    if (!(V.get_argent_en_plus()==0)) {
        argent+= V.get_argent_en_plus();
        V.set_argent_en_plus(0);
    }
}


int Menu::get_latence(Vague V) {
    return V.get_latence();
}


bool Menu::fin_de_partie() {
    return (vie==0);
}


bool Menu::est_sur_chemin(IntPoint2 position, Carte C) {
    bool b=false;
    for (int i=0; i<C.get_longueur(); i++) {
        bool b1x, b1y, b2x, b2y, m;
        b1y= (longueur_case*position[1]> C.get_coordonnee(i,1)-C.get_largeur()/2) && (longueur_case*position[1]< C.get_coordonnee(i,1)+C.get_largeur()/2);
        b2y= (longueur_case*position[1]+longueur_case> C.get_coordonnee(i,1)-C.get_largeur()/2) && (longueur_case*position[1]+longueur_case< C.get_coordonnee(i,1)+C.get_largeur()/2);

        b1x= (longueur_case*position[0]> C.get_coordonnee(i,0)-C.get_largeur()/2) && (longueur_case*position[0]< C.get_coordonnee(i,0)+C.get_largeur()/2);
        b2x= (longueur_case*position[0]+longueur_case> C.get_coordonnee(i,0)-C.get_largeur()/2) && (longueur_case*position[0]+longueur_case< C.get_coordonnee(i,0)+C.get_largeur()/2);

        m= (longueur_case*position[1]>=height_fenetre);
        if ((b1x && b1y) || (b2x && b2y) || m)
            b=true;
    }
    return b;
}




//--------------------------Méthodes de la classe Rectangle--------------------------
Rectangle::Rectangle(int x0, int y0, int w0, int h0, bool plein0, int p, Color col0) {
    x=x0; y=y0; w=w0; h=h0; col=col0; plein= plein0;
    prix= p;
}

Rectangle::Rectangle(IntPoint2 p1, IntPoint2 p2,  bool plein0, Color col0) {
    x=p1[0]; y=p1[1]; w=abs(p1[0]-p2[0]); h=abs(p1[1]-p2[1]); col=col0; plein=plein0;
}

bool Rectangle::est_dedans(int xc, int yc) {
    if (xc>=x && xc<(x+w) && yc>=y && yc<=(y+h))
        return true;
    else
        return false;
}


void Rectangle::affiche() {
    if (plein)
        fillRect(x, y, w, h, col);
    else
        drawRect(x, y, w, h, col);
    if (prix>0)
        drawString(x+3, y+h-4, std::to_string(prix) + "$", BLACK, 10);
}

Rectangle::Rectangle() {
    x=0; y=0; w=0; h=0; col=BLACK; plein= true; prix=0;
}
