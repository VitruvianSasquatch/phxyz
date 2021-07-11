#ifndef SHAPE2_H
#define SHAPE2_H

#include "common.h"
#include "maths/vec2.h"

typedef struct {
	float rBound;
	size_t nPoints;
	Vec2_t *vertices; //Defined anticlockwise. 
} Shape2_t;


Shape2_t shape2_init(size_t nPoints, ...);

Shape2_t shape2_initRegular(size_t nPoints, float rVertex);

bool shape2_boundsIntersect(Shape2_t *shape1, Shape2_t *shape2);

Vec2_t shape2_intersectVector(Shape2_t *shape1, Shape2_t *shape2);



#endif //SHAPE2_H