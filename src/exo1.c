#include <g2x.h>


#define VECTREF 0.1

G2Xpoint A;
G2Xvector v;

/* dimension fenêtre (pixels) */
static int WWIDTH=512, WHEIGHT=512;
/* zone de travail réelle */
static double wxmin=-10.,wymin=-10.,wxmax=+10.,wymax=+10.;

/* fonction d'initialisation */
static void init(void) { 
  // srand(getpid());
  A = g2x_RandPoint(10);
  v = g2x_RandVector(VECTREF);

}

/* fonction de contrôle */
static void ctrl(void) { }

/* fonction de contrôle */
static void evts(void) { }

/* fonction de dessin   */
static void draw(void) { 
  g2x_Plot(A.x, A.y, G2Xr, 5);

}

/* fonction d'animation */
static void anim(void) { 

  if (A.x <= g2x_GetXMin()) { 
    v.x *= -1; 
    A.x = g2x_GetXMin() + v.x; 
  } else  if (A.x >= g2x_GetXMax()) { 
    v.x *= -1; 
    A.x = g2x_GetXMax() + v.x; 
  } else  if (A.y <= g2x_GetYMin()) { 
    v.y *= -1; 
    A.y = g2x_GetYMin() + v.y; 
  } else  if (A.y >= g2x_GetYMax()) { 
    v.y *= -1; 
    A.y = g2x_GetYMax() + v.y; 
  } else{
    A.x += v.x;
    A.y += v.y;
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
  g2x_SetCtrlFunction(NULL); /* fonction de contrôle      */
  g2x_SetEvtsFunction(NULL); /* fonction d'événements     */
  g2x_SetDrawFunction(draw); /* fonction de dessin        */
  g2x_SetAnimFunction(anim); /* fonction d'animation      */
  g2x_SetExitFunction(NULL); /* fonction de sortie        */

  /* boucle principale */
  return g2x_MainStart();
}
