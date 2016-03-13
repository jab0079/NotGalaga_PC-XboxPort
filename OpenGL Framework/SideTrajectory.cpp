#include "object.h"
#include "Sprite.h"
#include "field.h"
#include "FieldManager.h"
#include "SideTrajectory.h"

const float SideTrajectory::SIDESPEED = SIDE_TRAJECTORY_SPEED;

SideTrajectory::SideTrajectory(Sprite* sprite)
{
	mSprite = sprite;
	mPosition = *mSprite->getPosition();

	mSpeed = SideTrajectory::SIDESPEED;
}


SideTrajectory::~SideTrajectory()
{}

void SideTrajectory::update(uint32_t milliseconds)
{
	mPosition.x += mSpeed * milliseconds / 1000;

	checkBoundary();
}

void SideTrajectory::checkBoundary()
{
	FieldC *field = FieldManagerC::GetInstance()->getFieldPtr();
	float_t leftSide = field->getPosition()->x - ((float_t)field->getWidth() / 2.0f);
	float_t rightSide = field->getPosition()->x + ((float_t)field->getWidth() / 2.0f);
	float_t topSide = field->getPosition()->y - ((float_t)field->getHeight() / 2.0f);
	float_t bottomSide = field->getPosition()->y + ((float_t)field->getHeight() / 2.0f);

	float_t spriteLeft = mPosition.x - mSprite->getWidth() / 2;
	float_t spriteRight = mPosition.x + mSprite->getWidth() / 2;
	float_t spriteUp = mPosition.y - mSprite->getHeight() / 2;
	float_t spriteDown = mPosition.y + mSprite->getHeight() / 2;

	if (spriteLeft <= leftSide)
	{
		mSpeed *= -1.0f;
		mPosition.x = leftSide + mSprite->getWidth() / 2;
	}
	else if (spriteRight >= rightSide)
	{
		mSpeed *= -1.0f;
		mPosition.x = rightSide - mSprite->getWidth() / 2;
	}
}