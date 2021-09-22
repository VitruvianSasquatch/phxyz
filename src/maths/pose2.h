#ifndef POSE2_H
#define POSE2_H

#include "common.h"
#include "maths/vec2.h"

typedef struct {
	Vec2_t position;
	double orientation;
} Pose2_t;


Pose2_t pose2_init(Vec2_t position, double orientation);

Pose2_t pose2_transformPose(Pose2_t base, Pose2_t applied);

Vec2_t pose2_transformVec(Vec2_t vec, Pose2_t pose);


#endif //POSE2_H