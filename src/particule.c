#include "particule.h"

void part_move(Particule *part){
	part->pos.x += part->vit.n * part->vit.u.x;
	part->pos.y += part->vit.n * part->vit.u.y;
}

void part_bounce(Particule *part){
  if (part->pos.x < g2x_GetXMin())
    part->vit.u.x *= -1; 
  if (part->pos.x > g2x_GetXMax())
    part->vit.u.x *= -1; 
  if (part->pos.y < g2x_GetYMin())
    part->vit.u.y *= -1; 
  if (part->pos.y > g2x_GetYMax())
    part->vit.u.y *= -1; 

}

void part_cross(Particule *part){
	if (part->pos.x < g2x_GetXMin()) { 
    part->pos.x = g2x_GetXMax(); 
  } 
  if (part->pos.x > g2x_GetXMax()) { 
    part->pos.x = g2x_GetXMin(); 
  }
  if (part->pos.y < g2x_GetYMin()) { 
    part->pos.y = g2x_GetYMax(); 
  }
  if (part->pos.y > g2x_GetYMax()) { 
    part->pos.y = g2x_GetYMin(); 
  }
}

void part_draw(Particule *part){
	g2x_DrawFillCircle(part->pos, part->ray, part->col);
}

bool part_pursuit(Particule *a, Particule *b, double alpha){
  if(alpha == 0)
    return false;
  Traj ab = traj_2p(a->pos, b->pos);
  

  double d = ab.n;
  if(d < a->ray + b->ray)
    return false;

  G2Xvector Va;
  Va.x = ((1. - alpha) * a->vit.n * a->vit.u.x) + (alpha * b->vit.n * ab.u.x);
  Va.y = ((1. - alpha) * a->vit.n * a->vit.u.y) + (alpha * b->vit.n * ab.u.y); 
  
  a->vit.n = sqrt(pow(Va.x, 2) + pow(Va.y, 2));
  a->vit.u.x = (1/a->vit.n) * Va.x;
  a->vit.u.y = (1/a->vit.n) * Va.y;

  return true;
}

bool part_track(Particule *a, G2Xpoint *pos, double alpha) {
  if (alpha == 0) 
    return false;
  
  G2Xvector M = g2x_Vector2p(a->pos, *pos);
  double d = sqrt(M.x * M.x + M.y * M.y);

  if(d < 2 * a->ray)
    return false;

  G2Xvector Va;
  Va.x = ((1. - alpha) * a->vit.n * a->vit.u.x) + (alpha * M.x);
  Va.y = ((1. - alpha) * a->vit.n * a->vit.u.y) + (alpha * M.y); 

  double norm = sqrt(Va.x * Va.x + Va.y * Va.y);
  if(norm > 0) {
    Va.x /= norm;
    Va.y /= norm;

    a->vit.u.x = Va.x;
    a->vit.u.y = Va.y;
    a->vit.n = a->vit.n;
  }
  
  return true;
}

void part_insert_between(Particule *prev, Particule *new, Particule *next) {
  if(prev) {
    prev->suiv = new;
  }
  if(next) {
    next->prec = new;
  }
  new->prec = prev;
  new->suiv = next;
}
