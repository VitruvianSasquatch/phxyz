#ifndef PHXY_H
#define PHXY_H

#include "common.h"
#include "body.h"

typedef struct {
	size_t numBodies;
	Body_t *bodies;
	bool *isUsed;
} Phxy_t;

typedef size_t PhxyId_t;

/**
 * @brief Initialises a new physics environment. 
 * 
 * @return Phxy_t A physics environment. 
 */
Phxy_t phxy_init(void);


/**
 * @brief Steps the physics environment @p phxy by @p dt seconds. 
 * 
 * @param phxy The physics environment to be updated. 
 * @param dt The timestep by which to move. 
 */
void phxy_update(Phxy_t *phxy, double dt);


PhxyId_t phxy_addBody(Phxy_t *phxy, Body_t body);


void phxy_applyImpulse(Phxy_t *phxy, PhxyId_t id, Vec2_t impulse);

#endif //PHXY_H