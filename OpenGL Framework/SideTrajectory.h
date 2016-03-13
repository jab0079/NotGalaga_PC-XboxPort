#ifndef _SIDE_TRAJECTORY_H_
#define _SIDE_TRAJECTORY_H_

#include "jsy/jsy.h"
#include "gamedefs.h"
#include "Trajectory.h"

class SideTrajectory : public Trajectory
{
public:
	SideTrajectory(Sprite* sprite);
	~SideTrajectory();

	void update(uint32_t milliseconds);

private:
	static const float_t SIDESPEED;

	float_t mSpeed;

	void checkBoundary();
};

#endif