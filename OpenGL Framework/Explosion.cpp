#define EXPLOSION_CPP

#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include "jsy/jsy.h"
#include "collInfo.h"
#include "object.h"
#include "Sprite.h"
#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "SpriteManager.h"

#include "Explosion.h"

Explosion::Explosion(float_t initPosX, float_t initPosY, uint32_t explosionType, uint32_t pointType)
{
	// Object
	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mVelocity.x = 0.0f;
	mVelocity.y = 0.0f;
	mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

	// Sprite
	if (explosionType == SpriteManager::EXPLOSION_PLAYER)
	{
		mWidth = EXPLOSION_PLAYER_WIDTH;
		mHeight = EXPLOSION_PLAYER_HEIGHT;
		mNumSprites = EXPLOSION_NUM_SPRITES;
	}
	else if (explosionType == SpriteManager::EXPLOSION_ENEMY)
	{
		mWidth = EXPLOSION_ENEMY_WIDTH;
		mHeight = EXPLOSION_ENEMY_HEIGHT;
		mNumSprites = EXPLOSION_NUM_SPRITES;
	}
	
	mCurrentSprite = START; // No animations

	mType = explosionType;

	mEnabled = true;
	mIsFacingLeft = false;

	// Explosion
	mIsFinished = false;
	mPointType = pointType;
	mAnimationTimer = 0;
	mAnimationRate = EXPLOSION_RATE_MS;
}


Explosion::~Explosion()
{}

bool8_t Explosion::CycleExplosionAnimation(uint32_t milliseconds)
{
	mAnimationTimer += milliseconds;
	if (mAnimationTimer < EXPLOSION_RATE_MS)
	{
		return false;
	}
	else
	{
		mAnimationTimer = 0;

		if (mType == SpriteManager::EXPLOSION_PLAYER)
		{
			mIsFinished = (mCurrentSprite == END);
			if (!mIsFinished)
			{
				mCurrentSprite++;
			}
		}
		else if (mType == SpriteManager::EXPLOSION_ENEMY)
		{
			if (mCurrentSprite == END)
			{
				mType = SpriteManager::POINTS;
				mCurrentSprite = mPointType;
				mWidth = POINTS_WIDTH;
				mHeight = POINTS_HEIGHT;
				mNumSprites = POINTS_NUM_SPRITES;
				mAnimationRate = POINTS_RATE_MS;
			}
			else if (!mIsFinished)
			{
				mCurrentSprite++;
			}
		}
		else if (mType == SpriteManager::POINTS)
		{
			mIsFinished = true;
		}

		

		return mIsFinished;
	}
	
}
