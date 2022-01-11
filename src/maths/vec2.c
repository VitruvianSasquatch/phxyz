#include <math.h>
#include "common.h"
#include "maths/pose2.h"

#include "vec2.h"


Vec2_t vec2_sum(Vec2_t v1, Vec2_t v2)
{
	Vec2_t ans = {v1.x + v2.x, v1.y + v2.y};
	return ans;
}

Vec2_t vec2_diff(Vec2_t v1, Vec2_t v2)
{
	Vec2_t ans = {v1.x - v2.x, v1.y - v2.y};
	return ans;
}

Vec2_t vec2_scale(Vec2_t v, double a)
{
	Vec2_t ans = {v.x * a, v.y * a};
	return ans;
}

double vec2_mag(Vec2_t v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

Vec2_t vec2_norm(Vec2_t v)
{
	return vec2_scale(v, 1/vec2_mag(v));
}

double vec2_dot(Vec2_t v1, Vec2_t v2)
{
	double ans = v1.x*v2.x + v1.y*v2.y;
	return ans;
}


double vec2_cross(Vec2_t v1, Vec2_t v2)
{
	double ans = v1.x*v2.y - v1.y*v2.x;
	return ans;
}


double vec2_squareDist(Vec2_t v1, Vec2_t v2)
{
	double xDiff = (v1.x-v2.x);
	double yDiff = (v1.y-v2.y);
	return xDiff*xDiff + yDiff*yDiff;
}


void vec2_print(Vec2_t v) {
	printf("(%.2lf, %.2lf)", v.x, v.y);
}



/*********************************
 * Begin line-specific functions *
 *********************************/



//TODO: Check
/**
 * @brief Determine whether a given sequence of points curves left or right. 
 * 
 * @param p1 The first point. 
 * @param p2 The second point. 
 * @param p3 The third point. 
 * @return double The measure of curvature. Left is widershins and therefore positive, right is clockwise and therefore negative. 
 */
static double direction(Vec2_t p1, Vec2_t p2, Vec2_t p3)
{
	return vec2_cross(vec2_diff(p2, p1), vec2_diff(p3, p2));
}


bool vec2_lineIntersect(Vec2_t a1, Vec2_t a2, Vec2_t b1, Vec2_t b2)
{
	double d1 = direction(b1, b2, a1);
	double d2 = direction(b1, b2, a2);
	double d3 = direction(a1, a2, b1);
	double d4 = direction(a1, a2, b2);

	//Line crossing check:
	//if ( ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
	return (d1*d2 < 0 && d3*d4 < 0);

	//Could also check whether endpoints are on the line. 
}


Vec2_t vec2_lineNormal(Vec2_t p1, Vec2_t p2)
{
	Vec2_t v = vec2_diff(p2, p1);
	Vec2_t n = {v.y, -v.x};
	return vec2_norm(n);
}