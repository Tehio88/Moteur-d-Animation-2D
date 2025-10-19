#include "particule.h"
#include "snake.h"

void init_chain(Snake *S, Particule *head, G2Xcolor col, double ray, double beta) {
    S->head = head;
    S->tail = head;
    S->col = col;
    S->ray = ray;
    S->beta = beta;

    head->suiv = NULL;
    head->prec = NULL;
    head->col = col;
    head->ray = ray;
}

int collision_snake_part(Particule head, Particule part) {
	double d = sqrt(pow(head.pos.x - part.pos.x, 2) + pow(head.pos.y - part.pos.y, 2));
    if (d < (head.ray + part.ray))
		return 1;
	return 0;
}

void snake_eat_part(Snake *S, Particule *p) {
	if(!p->est_mangee && collision_snake_part(*(S->head), *p)) {
		p->est_mangee = true;
		p->col = S->col;
		p->ray = S->tail->ray * 0.95;
		part_insert_between(S->tail, p, NULL);
		S->tail = p;
		p->pos = S->tail->pos;
	}
}

void snake_draw(Snake *S) {
	Particule * tmp = S->head;
	while(tmp) {
		g2x_DrawFillCircle(tmp->pos, tmp->ray, tmp->col);
		tmp = tmp->suiv;
	}
}

void snake_move(Snake *S) {
	part_move(S->head);
	Particule * p = S->head->suiv;
	while(p) {
		part_pursuit(p, p->prec, S->beta);
		part_move(p);
		p = p->suiv;
	}
}

void snake_track(Snake *S, G2Xpoint *pos, double alpha) {
	if(S && pos) {
		part_track(S->head, pos, alpha);
	}
}

void snake_bounce(Snake *S) {
	if(S->head) {
		if (S->head->pos.x < g2x_GetXMin())
			S->head->vit.u.x *= -1; 
		if (S->head->pos.x > g2x_GetXMax())
	    	S->head->vit.u.x *= -1; 
	  	if (S->head->pos.y < g2x_GetYMin())
	    	S->head->vit.u.y *= -1; 
	  	if (S->head->pos.y > g2x_GetYMax())
	    	S->head->vit.u.y *= -1; 
	}
}
