#ifndef _FOLLOW_TRAJECTORY_H_
#define _FOLLOW_TRAJECTORY_H_

#include "jsy/jsy.h"
#include "gamedefs.h"
#include "FieldManager.h"
#include "SpriteManager.h"
#include "Trajectory.h"

class FollowTrajectory : public Trajectory
{
public:
	FollowTrajectory(Sprite* sprite);
	~FollowTrajectory();

	void update(uint32_t milliseconds);
};

#endif