#include <g2x.h>
#include "particule.h"
#include "traj.h"

#define VECTREF 0.1
#define NB_PART 15
static void (*edge)(Particule *);

static bool FLAG;

Particule particules[NB_PART];
double alpha = 0;
G2Xpoint *mouse=NULL;

/* dimension fenêtre (pixels) */
static int WWIDTH=512, WHEIGHT=512;
/* zone de travail réelle */
static double wxmin=-10.,wymin=-10.,wxmax=+10.,wymax=+10.;

/* fonction d'initialisation */
static void init(void) { 
  srand(getpid());
  
  for(int i = 0; i < NB_PART; i++) {
    particules[i].pos = g2x_RandPoint(1.);
    particules[i].vit = traj_un(g2x_RandVector(VECTREF), 1);
    particules[i].ray = 0.5;
    particules[i].col =  g2x_h110_rgba_1f(i);
  }

  FLAG=false;

}

/* fonction de contrôle */
static void ctrl(void) {
  g2x_CreateSwitch("cross/bounce", &FLAG, "change le mode de colision de la particule");
  g2x_CreateScrollh_d("alpha", &alpha, 0.00, 0.25, "change la valeur de alpha");
  mouse = NULL; 
  if (g2x_MouseInWindow(.1))
    mouse = g2x_GetMousePosition(); 
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
  for(int i = 0; i < NB_PART; i++) {
    g2x_DrawFillCircle(particules[i].pos, 0.5, particules[i].col); 
  }

}

/* fonction d'animation */
void anim(void) {
  if (mouse != NULL) {
    for(int i = 0; i < NB_PART; i++) {
      part_track(&particules[i], mouse, alpha);
      part_move(&particules[i]);
      edge(&particules[i]);
    }
    
  }
  
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

