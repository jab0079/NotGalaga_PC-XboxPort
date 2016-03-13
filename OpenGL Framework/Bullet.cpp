#ifndef _BULLET_MANAGER_H
#define _BULLET_MANAGER_H


#include <iostream>
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include "jsy/jsy.h"

#include "Object.h"
#include "Sprite.h"
#include "Bullet.h"
#include "SpriteManager.h"
#include "gamedefs.h"


Bullet::Bullet(float_t x, float_t y, float_t xVel, float_t yVel, int32_t objectType, int32_t ownerType)
{
	//moved from .h
homingMissile = false;

	// Object
	mPosition.x = x;
	mPosition.y = y;
	mVelocity.x = xVel;
	mVelocity.y = yVel;
	mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

	// Sprite
	mWidth = MISSILE_WIDTH;
	mHeight = MISSILE_HEIGHT;
	mNumSprites = MISSILE_NUM_SPRITES;
	mCurrentSprite = 0;

	mType = objectType;

	mEnabled = true;
	mIsFacingLeft = false;

	// Bullet
	mOwnerType = ownerType;
}


Bullet::~Bullet()
{
}
void Bullet::UpdateBullet(uint32_t milliseconds) {
	if (homingMissile) {
		Enemy* nearestEnemy = SpriteManager::GetInstance()->GetNearestEnemy(this);
		if (nearestEnemy != nullptr) {
			float_t xDifference = nearestEnemy->getPosition()->x - getPosition()->x;
			float_t yDifference = nearestEnemy->getPosition()->y - getPosition()->y;
			float_t xyMagnitude = sqrtf(pow(xDifference, 2) + pow(yDifference, 2));
			float_t xNormalized = xDifference / xyMagnitude;
			float_t yNormalized = yDifference / xyMagnitude;
			float_t xVelocity = getVelocity()->x + xNormalized * HOMING_ABILITY;
			float_t yVelocity = getVelocity()->y;
			setVelocity(xVelocity, yVelocity);
		}
	}
}

#endif
