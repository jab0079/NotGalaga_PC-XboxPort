
#include "Sprite.h"
#include "Trajectory.h"

Trajectory::Trajectory()
{
}

Trajectory::Trajectory(const Vector2D & position)
{
	//moved from .h
tickCount = 0;

    mPosition.x = position.x;
    mPosition.y = position.y;
    mOriginalPosition.x = position.x;
    mOriginalPosition.y = position.y;
}


Trajectory::~Trajectory()
{
}

void Trajectory::GetPosition(Vector2D & position) const {
    position.x = mPosition.x;
    position.y = mPosition.y;
}

void Trajectory::SetPosition(const Vector2D & position) {
    mPosition.x = position.x;
    mPosition.y = position.y;
    mOriginalPosition.x = position.x;
    mOriginalPosition.y = position.y;
}

void Trajectory::reset() {
    mPosition.x = mOriginalPosition.x;
    mPosition.y = mOriginalPosition.y;
    tickCount = 0;
}

