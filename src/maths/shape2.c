#include "common.h"
#include "maths/vec2.h"

#include "maths/shape2.h"


Shape2_t shape2_initPoly(size_t nPoints, ...)
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

Shape2_t shape2_initRegPoly(size_t nPoints, float rVertex)
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

Shape2_t shape2_initCircle(float r)
{
	Shape2_t ans = {r, 0, NULL};
	return ans;
}