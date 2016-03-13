#include "object.h"
#include "Sprite.h"
#include "field.h"
#include "FieldManager.h"
#include <math.h>
#include "FallTrajectory.h"

const float FallTrajectory::FALLSPEED = FALL_TRAJECTORY_SPEED;

FallTrajectory::FallTrajectory(Sprite* sprite)
{
	mSprite = sprite;
	mPosition = *mSprite->getPosition();
}


FallTrajectory::~FallTrajectory()
{
}

void FallTrajectory::update(uint32_t milliseconds) {
    mPosition.y -= FallTrajectory::FALLSPEED * milliseconds / 1000;
    mPosition.x = 50.0f * (float_t) sin(mPosition.y / 20) + mOriginalPosition.x;
	checkBoundary();
}

void FallTrajectory::checkBoundary()
{
	FieldC *field = FieldManagerC::GetInstance()->getFieldPtr();
	float_t topSide = field->getPosition()->y - ((float_t)field->getHeight() / 2.0f);
	float_t bottomSide = field->getPosition()->y + ((float_t)field->getHeight() / 2.0f);

	float_t spriteUp = mPosition.y - mSprite->getHeight() / 2;
	float_t spriteDown = mPosition.y + mSprite->getHeight() / 2;

	if ((spriteDown <= topSide))
	{
		mPosition.y = bottomSide + mSprite->getHeight() / 2;
	}
}