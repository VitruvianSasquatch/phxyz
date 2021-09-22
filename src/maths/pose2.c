#include "common.h"
#include "maths/vec2.h"

#include "maths/pose2.h"


Pose2_t pose2_init(Vec2_t position, double orientation)
{
	Pose2_t ans = {position, orientation};
	return ans;
}

Pose2_t pose2_transformPose(Pose2_t base, Pose2_t applied)
{
	Pose2_t ans = base; //TODO: IMPLEMENT ME
	return ans;
}


Vec2_t pose2_transformVec(Vec2_t vec, Pose2_t pose)
{
	Vec2_t ans;
	ans.x = vec.x*cos(pose.orientation) - vec.y*sin(pose.orientation);
	ans.x += pose.position.x;
	ans.y = vec.x*sin(pose.orientation) + vec.y*cos(pose.orientation);
	ans.y += pose.position.y;
	return ans;
}