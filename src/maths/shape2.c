#include "common.h"
#include "maths/vec2.h"

#include "maths/shape2.h"


Shape2_t shape2_initPoly(size_t nPoints, ...)
{
	Shape2_t shape;
	shape.nPoints = nPoints;
	shape.vertices = calloc(nPoints, sizeof(double));
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


Shape2_t shape2_initRegPoly(size_t nPoints, double rVertex)
{
	Shape2_t shape;
	shape.nPoints = nPoints;
	shape.vertices = calloc(nPoints, sizeof(Vec2_t));
	shape.rBound = rVertex;
	for (size_t i = 0; i < nPoints; i++) {
		shape.vertices[i] = (Vec2_t){cos(i*2*PI/nPoints), sin(i*2*PI/nPoints)}; //TODO: test
	}
	return shape;
}


Shape2_t shape2_initCircle(double r)
{
	Shape2_t ans = {r, 0, NULL};
	return ans;
}


double shape2_area(const Shape2_t *shape)
{
	double area = 0;
	for (size_t i = 0; i < shape->nPoints-1; i++) {
		area += vec2_cross(shape->vertices[i], shape->vertices[i+1]);
	}
	area += vec2_cross(shape->vertices[shape->nPoints-1], shape->vertices[0]);
	return area/2;
}


double shape2_unitInertia(const Shape2_t *shape)
{
	double num = 0;
	double denom = 0;
	for (size_t i = 0; i < shape->nPoints-1; i++) {
		double cross = vec2_cross(shape->vertices[i], shape->vertices[i+1]);
		num += cross * vec2_squareMag(shape->vertices[i]) * vec2_dot(shape->vertices[i], shape->vertices[i+1]) * vec2_squareMag(shape->vertices[i+1]);
		denom += cross;
	}
	double cross = vec2_cross(shape->vertices[shape->nPoints-1], shape->vertices[0]);
	num += cross * vec2_squareMag(shape->vertices[shape->nPoints-1]) * vec2_dot(shape->vertices[shape->nPoints-1], shape->vertices[0]) * vec2_squareMag(shape->vertices[0]);
	denom += cross;

	return num / (6*denom);
}

