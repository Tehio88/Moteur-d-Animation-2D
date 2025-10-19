#include "obstacle.h"
#include "particule.h"


void part_draw_obs(Obstacle *obs){
  g2x_DrawFillCircle(obs->pos, obs->ray, obs->col);
}

bool part_bypass_circle(Particule *p, Obstacle *C, double omega) {
    G2Xvector u = p->vit.u;
    G2Xvector AC = g2x_Vector2p(p->pos, C->pos);
    
    double t = AC.x * u.x + AC.y * u.y;
    if (t < 0.0)
        return false;
    
    double d = AC.x * u.y - AC.y * u.x;
    if (d > C->ray)
        return false;
    G2Xvector CP = {AC.x - t * u.x, AC.y - t * u.y};
    double alpha = pow((C->ray / t), omega);
    
    p->vit.u.x = (1 - alpha) * u.x + alpha * CP.x / d;
    p->vit.u.y = (1 - alpha) * u.y + alpha * CP.y / d;

    return true;
}