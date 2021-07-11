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
	float m; //Mass
	Vec2_t x; //Position
	Vec2_t v; //Velocity

	float I; //Rotational Inertia (kgm^2)
	float theta; //Angular Position (rad)
	float omega; //Angular Velocity (rad/s)

	//Dynamic vars:
	Vec2_t F; //Force
	float tau; //Torque
} Body_t;


Body_t body_init(Vec2_t pos, Shape2_t shape, float m, float I);

void body_applyForce(Body_t *body, Vec2_t F);

void body_applyImpulse(Body_t *body, Vec2_t dp);

void body_collide(Body_t *b1, Body_t *b2, float F);

void body_update(Body_t *body, float dt);

#endif //BODY_H