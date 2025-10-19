#ifndef PART_H
#define PART_H


#include <g2x.h>
#include "traj.h"


typedef struct particule
{
	G2Xpoint pos; /* poistion */
	Traj vit; /* vitesse */
	G2Xcolor col; /* couleur */
	double ray; /* rayon */
	struct particule * prec;
	struct particule * suiv;
	bool est_mangee;
} Particule;

void part_move(Particule *part);

void part_bounce(Particule *part);

void part_cross(Particule *part);

void part_draw(Particule *part);

bool part_pursuit(Particule *a, Particule *b, double alpha);

bool part_track(Particule *a, G2Xpoint *pos, double alpha);

void part_insert_between(Particule *prev, Particule *new, Particule *next);

#endif