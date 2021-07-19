#ifndef POSE2_H
#define POSE2_H

#include "common.h"
#include "vec2.h"

typedef struct {
	Vec2_t position;
	float orientation;
} Pose2_t;


Pose2_t pose2_init(Vec2_t position, float orientation);

Pose2_t pose2_applied(Pose2_t base, Pose2_t applied);


#endif //POSE2_H