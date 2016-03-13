#ifndef _FALL_TRAJECTORY_H_
#define _FALL_TRAJECTORY_H_

#include "jsy/jsy.h"
#include "gamedefs.h"
#include "Trajectory.h"

class FallTrajectory :
    public Trajectory
{
public:
    FallTrajectory(Sprite* sprite);
    ~FallTrajectory();

    void update(uint32_t milliseconds);

private:
    static const float_t FALLSPEED;

	void checkBoundary();
};

#endif
