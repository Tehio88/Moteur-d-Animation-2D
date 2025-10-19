#ifndef OBS_H
#define OBS_H

#include <g2x.h>
#include "particule.h"

typedef struct {
    G2Xpoint pos;
    double ray;
    G2Xcolor col;
} Obstacle;

void part_draw_obs(Obstacle *obs);

bool part_bypass_circle(Particule *p, Obstacle *C, double omega);

#endif