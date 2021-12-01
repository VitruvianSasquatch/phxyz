#include "common.h"
#include "maths/vec2.h"
#include "maths/pose2.h"
#include "maths/shape2.h"

#include "body.h"


Body_t body_init(Vec2_t pos, Shape2_t shape, double m, double I)
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


void body_update(Body_t *body, double dt)
{
	if (!body->isLocked && body->isActive) {
		//Linear:
		Vec2_t a = vec2_scale(body->F, 1/body->m);
		body->F = VEC2_ZERO;
		Vec2_t dv = vec2_scale(a, dt);
		body->v = vec2_sum(body->v, dv);
		Vec2_t dx = vec2_scale(body->v, dt);
		body->x = vec2_sum(body->x, dx);

		//Rotational:
		double alpha = body->tau/body->I;
		body->tau = 0;
		double domega = alpha*dt;
		body->omega += domega;
		double dtheta = body->omega*dt;
		body->theta += dtheta;
	}
}





bool body_couldCollide(const Body_t *body1, const Body_t *body2)
{
	return vec2_squareDist(body1->x, body2->x) <= body1->shape.rBound + body2->shape.rBound; //Is inside bounding circle. 
}


bool body_isColliding(const Body_t *body1, const Body_t *body2)
{
	//FIXME: Consider doing the intersection check in the frame of one of the bodies?
	Vec2_t globalVerts1[body1->shape.nPoints];// = {VEC2_ZERO};
	memset(globalVerts1, 0, body1->shape.nPoints*sizeof(Vec2_t));
	Pose2_t globalPose1 = pose2_init(body1->x, body1->theta);
	for (size_t i = 0; i < body1->shape.nPoints; i++) {
		globalVerts1[i] = pose2_transformVec(body1->shape.vertices[i], globalPose1);
	}

	Vec2_t globalVerts2[body2->shape.nPoints];// = {VEC2_ZERO};
	memset(globalVerts2, 0, body2->shape.nPoints*sizeof(Vec2_t));
	Pose2_t globalPose2 = pose2_init(body2->x, body2->theta);
	for (size_t i = 0; i < body2->shape.nPoints; i++) {
		globalVerts2[i] = pose2_transformVec(body2->shape.vertices[i], globalPose2);
	}

	//TODO: test each line segment pair for intersection. For now, though, being lazy...
	return true;

}