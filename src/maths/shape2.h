#ifndef SHAPE2_H
#define SHAPE2_H

#include "common.h"
#include "maths/vec2.h"

typedef struct {
	double rBound; //0 for point. 
	size_t nPoints; //0 for circle. 
	Vec2_t *vertices; //Defined anticlockwise. 
} Shape2_t;


Shape2_t shape2_initPoly(size_t nPoints, ...);

Shape2_t shape2_initRegPoly(size_t nPoints, double rVertex);

Shape2_t shape2_initCircle(double r);

//Shape2_t shape2_transformed(const Shape2_t *shape, Pose2_t pose);



#endif //SHAPE2_H