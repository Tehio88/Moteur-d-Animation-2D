#include <g2x.h>
#include "particule.h"
#include "traj.h"

#define VECTREF 0.1
static void (*edge)(Particule *);

static bool FLAG;

Particule A;
Particule B;
double alpha = 0;

/* dimension fenêtre (pixels) */
static int WWIDTH=512, WHEIGHT=512;
/* zone de travail réelle */
static double wxmin=-10.,wymin=-10.,wxmax=+10.,wymax=+10.;

/* fonction d'initialisation */
static void init(void) { 
  srand(getpid());
  
  A.pos = g2x_RandPoint(1.);
  A.vit = traj_un(g2x_RandVector(VECTREF), 0.1);
  A.col = G2Xr;
  A.ray = 0.5;

  B.pos = g2x_RandPoint(0.1);
  B.vit = traj_un(g2x_RandVector(VECTREF), 0.1);
  B.col = G2Xr;
  B.ray = 0.5;
  

  FLAG=false;

}

/* fonction de contrôle */
static void ctrl(void) {
  g2x_CreateSwitch("cross/bounce", &FLAG, "change le mode de colision de la particule");
  g2x_CreateScrollh_d("alpha", &alpha, 0.00, 0.25, "change la valeur de alpha");
}

/* fonction de contrôle */
static void evts(void) { 
  
  if (FLAG == false){
    edge = part_bounce;
  }
  else if (FLAG == true)
    edge = part_cross;
}

/* fonction de dessin   */
static void draw(void) { 
  g2x_Plot(A.pos.x, A.pos.y, G2Xr, 5);
  g2x_Plot(B.pos.x, B.pos.y, G2Xb, 5);

}

/* fonction d'animation */
static void anim(void) {
  part_move(&A);
  part_move(&B);
  edge(&A);
  edge(&B);
  part_pursuit(&A, &B, alpha);
}

/* fonction de sortie   */
static void quit(void) { }

/************************/
/* fonction principale  */
/************************/
int main(int argc, char **argv)
{
  g2x_InitWindow(*argv,WWIDTH,WHEIGHT);
  g2x_SetWindowCoord(wxmin,wymin,wxmax,wymax);

  /*  fonctions -> handlers  */
  g2x_SetInitFunction(init); /* fonction d'initialisation */
  g2x_SetCtrlFunction(ctrl); /* fonction de contrôle      */
  g2x_SetEvtsFunction(evts); /* fonction d'événements     */
  g2x_SetDrawFunction(draw); /* fonction de dessin        */
  g2x_SetAnimFunction(anim); /* fonction d'animation      */
  g2x_SetExitFunction(NULL); /* fonction de sortie        */

  /* boucle principale */
  return g2x_MainStart();
}
