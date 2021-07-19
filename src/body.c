#include "common.h"
#include "maths/vec2.h"
#include "maths/shape2.h"

#include "body.h"


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





bool body_couldCollide(const Body_t *body1, const Body_t *body2)
{
	return vec2_squareDist(body1->x, body2->x) <= body1->shape.rBound + body2->shape.rBound; //Is inside bounding circle. 
}


bool body_isColliding(Body_t *body1, Body_t *body2)
{
	//TODO
}