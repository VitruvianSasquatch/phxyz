#include "common.h"
#include "body.h"
#include "phxy.h"

#define PHXY_INIT_NUM_BODIES 1024

Phxy_t phxy_init(void)
{
	Phxy_t phxy;
	phxy.numBodies = PHXY_INIT_NUM_BODIES;
	phxy.isUsed = calloc(phxy.numBodies, sizeof(bool));
	phxy.bodies = calloc(phxy.numBodies, sizeof(Body_t));
	if (phxy.bodies != NULL) {
		return phxy;
	} //If we don't have enough heap for that, we have a problem. 
	puts("Out of heap memory.");
	return phxy;
}


void phxy_update(Phxy_t *phxy, double dt)
{
	//TODO: Check collisions. 
	for (size_t i = 0; i < phxy->numBodies; i++) {
		if (phxy->isUsed[i]) {
			body_update(&phxy->bodies[i], dt);
		}
	}
}


PhxyId_t phxy_addBody(Phxy_t *phxy, Body_t body)
{
	size_t i = 0;
	while (phxy->isUsed[i] && i < phxy->numBodies) {
		i++;
	}
	if (i == phxy->numBodies) {
		phxy->numBodies *= 2;
		phxy->bodies = reallocarray(phxy->bodies, phxy->numBodies, sizeof(Body_t));
	}
	phxy->bodies[i] = body;
	phxy->isUsed[i] = true;
	return i;

}


void phxy_applyImpulse(Phxy_t *phxy, PhxyId_t id, Vec2_t dp)
{
	body_applyImpulse(&phxy->bodies[id], dp);
}