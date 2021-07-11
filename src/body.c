#include "common.h"
#include "maths/vec2.h"
#include "maths/shape2.h"

#include "body.h"


/**
 * @brief Initialises a body with a desired mass @p m and position @p pos . 
 * 
 * @param pos The initial position of the body. 
 * @param shape The geometry of the body. 
 * @param m The mass of the body. 
 * @param I The inertia of the body. 
 * @return Body_t The body with the specified mass and position, with all other state variables zeroed. 
 */
Body_t body_init(Vec2_t pos, Shape2_t shape, float m, float I)
{
	Body_t body = {
		.isLocked = false,
		.isActive = true,

		.shape = shape,

		.m = m, 
		.x = pos, 
		.v = VEC2_ZERO,

		.I = I, 
		.theta = 0,
		.omega = 0,

		.F = VEC2_ZERO,
		.tau = 0
	};

	return body;
}

/**
 * @brief Adds @p F to the net forces acting on @p body for this update step. 
 * 
 * @param body A reference to the body to apply a force to. 
 * @param F The force to apply. 
 */
void body_applyForce(Body_t *body, Vec2_t F)
{
	if (!body->isLocked) {
		body->F = vec2_sum(body->F, F);
	}
}


void body_applyImpulse(Body_t *body, Vec2_t dp)
{
	if (!body->isLocked) {
		body->v = vec2_sum(body->v, vec2_scale(dp, 1/body->m));
	}
}


void body_collide(Body_t *b1, Body_t *b2, float F) {
	Vec2_t dirAB = vec2_norm(vec2_diff(b2->x, b1->x));
	body_applyForce(b1, vec2_scale(dirAB, F));
	body_applyForce(b2, vec2_scale(dirAB, -F));
}


/**
 * @brief Applies the accumulated net force and update the state of @p body via simple Euler integration. 
 * 
 * @param body A reference to the body to update. 
 * @param dt The time difference between the last call to this function. 
 */
void body_update(Body_t *body, float dt)
{
	if (!body->isLocked && !body->isActive) {
		//Linear:
		Vec2_t a = vec2_scale(body->F, 1/body->m);
		body->F = VEC2_ZERO;
		Vec2_t dv = vec2_scale(a, dt);
		body->v = vec2_sum(body->v, dv);
		Vec2_t dx = vec2_scale(body->v, dt);
		body->x = vec2_sum(body->x, dx);

		//Rotational:
		float alpha = body->tau/body->I;
		body->tau = 0;
		float domega = alpha*dt;
		body->omega += domega;
		float dtheta = body->omega*dt;
		body->theta += dtheta;
	}
}