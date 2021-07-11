#include "common.h"
#include "maths/vec2.h"

#include "maths/shape2.h"


Shape2_t shape2_init(size_t nPoints, ...)
{
	Shape2_t shape;
	shape.nPoints = nPoints;
	shape.vertices = calloc(nPoints, sizeof(float));
	shape.rBound = 0;
	
	va_list args;
	va_start(args, nPoints);

	for (size_t i = 0; i < nPoints; i++) {
		shape.vertices[i] = va_arg(args, Vec2_t);
		float rLocal = vec2_mag(shape.vertices[i]);
		shape.rBound = shape.rBound > rLocal ? shape.rBound : rLocal;
	}

	va_end(args);
	return shape;
}

Shape2_t shape2_initRegular(size_t nPoints, float rVertex)
{
	Shape2_t shape;
	shape.nPoints = nPoints;
	shape.vertices = calloc(nPoints, sizeof(float));
	shape.rBound = rVertex;
	for (size_t i = 0; i < nPoints; i++) {
		shape.vertices[i] = (Vec2_t){cosf(i*2*PI/nPoints), sinf(i*2*PI/nPoints)}; //TODO: test
	}
	return shape;
}

bool shape2_boundsIntersect(Shape2_t *shape1, Shape2_t *shape2);

Vec2_t shape2_intersectVector(Shape2_t *shape1, Shape2_t *shape2);