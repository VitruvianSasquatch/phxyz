#include "common.h"
#include "maths/vec2.h"

#include "maths/pose2.h"


Pose2_t pose2_init(Vec2_t position, float orientation)
{
	Pose2_t ans = {position, orientation};
	return ans;
}

Pose2_t pose2_applied(Pose2_t base, Pose2_t applied)
{
	Pose2_t ans = {base.}
}