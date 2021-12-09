#include "common.h"
#include "body.h"
#include "phxy.h"

Phxy_t phxy_init(void)
{
	Phxy_t phxy;
	//TODO: init body counts. 
}


void phxy_update(Phxy_t *phxy, double dt)
{
	//TODO: Check collisions. 
	for (size_t i = 0; i < phxy->numBodies; i++) {
		body_update(&phxy->bodies[i], dt);
	}
}