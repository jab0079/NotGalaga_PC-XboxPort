#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

#include "jsy/jsy.h"
#include "Sprite.h"

class Trajectory
{
public:
    Trajectory();
    Trajectory(const Vector2D & position);
    virtual ~Trajectory();

    virtual void update(uint32_t milliseconds) = 0;
    void reset();
    void GetPosition(Vector2D & position) const;
    void SetPosition(const Vector2D & position);

protected:
	Sprite* mSprite;
    Vector2D mPosition;
    Vector2D mOriginalPosition;
    uint32_t tickCount;
};

#endif