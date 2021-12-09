#ifndef PHXY_H
#define PHXY_H

#include "common.h"
#include "body.h"

typedef struct {
	size_t numBodies;
	Body_t *bodies;
} Phxy_t;

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

#endif //PHXY_H