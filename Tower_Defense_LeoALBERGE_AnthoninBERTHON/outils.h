#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;


const bool limite_argent=true;

const int width_fenetre=600;
const int height_fenetre=600;

const int frame_rate= 15;
const int longueur_case = 20;

const int nombre_case_x= width_fenetre/longueur_case;
const int nombre_case_y= height_fenetre/longueur_case;


const int latence_entre_vague=100;
const int latence_affichage_init= 3;

float distance(IntPoint2 p1, IntPoint2 p2);

void aligne_grille(IntPoint2 &p);


bool est_dans_rectangle(IntPoint2 p, IntPoint2 coin_gauche,int w, int h);


IntPoint2 centre(IntPoint2 p, int width=1, int height=1);

IntPoint2 grille_coord(IntPoint2 p);

void InitRandom();
int random_int(int a, int b);



const Color ORANGE= Color(254, 170, 73);
const Color VIOLET= Color(177, 0, 183);
const Color CCYAN= Color(0, 233, 225);
const Color GRIS_FONCE= Color(52, 52, 52);
const Color ROUGE_CHEMIN= Color(210, 72, 72);
const Color GRIS_MOINS_FONCE= Color(94, 94, 94);
const Color ROUGE_COEUR= Color(209, 2, 57);

