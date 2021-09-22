#ifndef BODY_H
#define BODY_H

#include "common.h"
#include "maths/vec2.h"
#include "maths/shape2.h"

typedef struct {
	//Enabling vars:
	bool isLocked;
	bool isActive;

	//Shape vars:
	Shape2_t shape; //CoM is at origin of shape. 

	//State vars:
	double m; //Mass
	Vec2_t x; //Position
	Vec2_t v; //Velocity

	double I; //Rotational Inertia (kgm^2)
	double theta; //Angular Position (rad)
	double omega; //Angular Velocity (rad/s)

	//Dynamic vars:
	Vec2_t F; //Force
	double tau; //Torque
} Body_t;


/**
 * @brief Initialises a body with a desired mass @p m and position @p pos . 
 * 
 * @param pos The initial position of the body. 
 * @param shape The geometry of the body. 
 * @param m The mass of the body. 
 * @param I The inertia of the body. 
 * @return Body_t The body with the specified mass and position, with all other state variables zeroed. 
 */
Body_t body_init(Vec2_t pos, Shape2_t shape, double m, double I);



/**
 * @brief Adds @p F to the net forces acting on @p body for this update step. 
 * 
 * @param body A reference to the body to apply a force to. 
 * @param F The force to apply. 
 */
void body_applyForce(Body_t *body, Vec2_t F);


void body_applyImpulse(Body_t *body, Vec2_t dp);


/**
 * @brief Applies the accumulated net force and torque and update the state of @p body via simple Euler integration. 
 * 
 * @param body A reference to the body to update. 
 * @param dt The time difference between the last call to this function. 
 */
void body_update(Body_t *body, double dt);


//----------------------Functions rather than methods---------------------


bool body_couldCollide(const Body_t *body1, const Body_t *body2);

bool body_isColliding(const Body_t *body1, const Body_t *body2);

#endif //BODY_H