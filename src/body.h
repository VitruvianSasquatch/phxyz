#ifndef BODY_H
#define BODY_H

#include "common.h"
#include "maths/vec2.h"
#include "maths/shape2.h"

//TODO: Consider restructuring as recommended in https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-core-engine--gamedev-7493


typedef struct {
	double density; //Density (kg/m^2)
	double restitution;
	double staticFriction;
	double dynamicFriction;
} Material_t;



typedef struct {
	//Enabling vars:
	bool isLocked;
	bool isActive;

	//Attribute vars:
	Shape2_t *shape; //CoM is at origin of shape. 
	Material_t *material;

	//State vars:
	double m; //Mass
	Vec2_t pos; //Position (m)
	Vec2_t v; //Velocity (m/s)

	double I; //Rotational Inertia (kgm^2)
	double theta; //Angular Position (rad)
	double omega; //Angular Velocity (rad/s)

	//Temporary vars:
	Vec2_t F; //Force (N)
	double tau; //Torque (Nm)
} Body_t;


/**
 * @brief Initialises a body with a specified position @p pos and material @p material . 
 * 
 * @param pos The initial position of the body. 
 * @param shape The geometry of the body. 
 * @param material The material of the body. 
 * @return Body_t The body with the specified material and position, with all other state variables zeroed. 
 */
Body_t body_init(Vec2_t pos, Shape2_t *shape, Material_t *material);


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