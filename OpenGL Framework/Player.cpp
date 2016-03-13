#define ET_CPP

#include <iostream>
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#include "jsy/jsy.h"
#include "collInfo.h"
#include "object.h"
#include "Sprite.h"
#include "Player.h"

#include "field.h"
#include "fieldmanager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "SpriteManager.h"
#include "game.h"


Player* Player::CreatePlayer(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, int32_t gameObjectType) {
	Player* player = new Player(initPosX, initPosY, initVelX, initVelY, gameObjectType);

    static uint32_t fireId = JsyAudioLoad(CGame::GetInstance()->GetJsyAudioHandle(), PLAYER_SFX_FIRE);
    static uint32_t hitId = JsyAudioLoad(CGame::GetInstance()->GetJsyAudioHandle(), PLAYER_SFX_HIT);

    player->mFireSFXId = fireId;
    player->mHitSFXId = hitId;
	return player;
}

Player::Player(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, int32_t gameObjectType)
{
//Moved from .h
	 currentWeapon = NORMAL;
	 mInvincible = false;
	 //for(int i = 0; i < MAX_PLAYER_LIVES; i++){
  //       mLives[i] = nullptr;
	 //}

	// Object
	mPosition.x = initPosX;
	mPosition.y = initPosY;
	mVelocity.x = initVelX;
	mVelocity.y = initVelY;
	mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

	// Sprite
	mWidth = PLAYER_WIDTH;
	mHeight = PLAYER_HEIGHT;
	mNumSprites = PLAYER_NUM_SPRITES;
	mCurrentSprite = 0; // No animations

	mType = gameObjectType;

	mEnabled = true;
	mIsFacingLeft = false;

	// Player
	mIsMoving = false;
	mCanMove = true;
	mCanShoot = true;
	mShotTimer = 0;

	mPowerupTimer = 0;
	mNumLives = STARTING_LIVES;
    bulletTime = PLAYER_BULLETTIME;
    inBulletTime = false;
    bulletTimeDebounce = false;

	for (int32_t i = 1; i <= MAX_PLAYER_LIVES; i++)
	{
		// Get position for lives based on screen size and half player's actual size to
		//	place them in the bottom-left corner;
		float_t xPos = (-BG_WIDTH / 2.0f) + i * (mWidth / 2.0f);
		float_t yPos = (-BG_HEIGHT / 2.0f) + (mHeight);
		mLives[i - 1] = new Sprite(xPos, yPos, mWidth / 2.0f, mHeight / 2.0f, SpriteManager::PLAYER);

		if (i > mNumLives)
			mLives[i -1]->disable();
	}
}

Player::~Player()
{
	for (int32_t i = 0; i < mNumLives; i++)
	{
		if (mLives[i] != nullptr) {
			delete mLives[i];
			mLives[i] = nullptr;
		}	
	}
}

bool8_t Player::IsInvincible(){
	return mInvincible;
}

void Player::EnableInvincible(){
	MInvincibleTimer = INVINCIBILITY_TIME;
	mInvincible = true;
}

void Player::update(uint32_t milliseconds)
{
	if(mInvincible){
		MInvincibleTimer -= milliseconds;
		if(MInvincibleTimer <= 0)
		{
			mInvincible = false;
		}
	}
    milliseconds = (float_t)milliseconds / CGame::GetInstance()->getFrameRatio();
    if (mEnabled)
    {
        mPosition.x += mVelocity.x * milliseconds / 10;
        mPosition.y += mVelocity.y * milliseconds / 10;
    }
}

void Player::updateET(uint32_t milliseconds)
{
    milliseconds = (float_t)milliseconds/CGame::GetInstance()->getFrameRatio();

    if (inBulletTime) {
        bulletTime -= (float_t)milliseconds / 1000.0f;
        if (bulletTime < 0.0f) {
            bulletTime = 0.0f;
            CGame::GetInstance()->setFrameRatio(1.0f);
            inBulletTime = false;
        }
    }
    else {
        bulletTime += ((float_t)milliseconds / 1000.0f) * PLAYER_BULLETTIME / 60.0f;
    }

	// Check if dead
	if (mNumLives < 0)
	{
		SpriteManager::GetInstance()->endGame();
		return;
	}

	// Update weapon powerup timer
	if (currentWeapon != NORMAL)
	{
		mPowerupTimer -= milliseconds;
		if (mPowerupTimer <= 0)
		{
			currentWeapon = NORMAL;
		}
	}

	// Update shot timer
	if (!mCanShoot)
	{
		mShotTimer += milliseconds;
		switch (currentWeapon) {
		case NORMAL:
			if (mShotTimer >= NORMAL_SHOT_RATE)
			{
				mCanShoot = true;
			}
			break;
		case QUICK:
			if (mShotTimer >= QUICK_SHOT_RATE)
			{
				mCanShoot = true;
			}
			break;
		case SPREAD:
			if (mShotTimer >= SPREAD_SHOT_RATE)
			{
				mCanShoot = true;
			}
			break;
		case HOMING:
			if (mShotTimer >= HOMING_SHOT_RATE)
			{
				mCanShoot = true;
			}
			break;
		default:
			mCanShoot = false;
			break;
		}
	}

	// Check for movement input if able to move
	if (mCanMove)
	{
		CheckForUserInput();
	}

	CheckBoundaries();
}

void Player::playerHit()
{
	mNumLives--;
    JsyAudioPlaySound(CGame::GetInstance()->GetJsyAudioHandle(), mHitSFXId);
	if (mNumLives >= 0)
	{
		mLives[mNumLives]->disable();
	}

}

void Player::AddExtraLife() {
	if (mNumLives < MAX_PLAYER_LIVES) {
		mLives[mNumLives]->enable();
		mNumLives++;
	}
}


void Player::CheckForUserInput()
{

    float_t keyLeft, keyRight, keyUp, keyDown, keyShoot, keyFrameRatio;

	JsyInputGetInput(CGame::GetInstance()->GetJsyInputHandle(), JSY_INPUT_LEFT, &keyLeft);
	JsyInputGetInput(CGame::GetInstance()->GetJsyInputHandle(), JSY_INPUT_RIGHT, &keyRight);
	JsyInputGetInput(CGame::GetInstance()->GetJsyInputHandle(), JSY_INPUT_UP, &keyUp);
	JsyInputGetInput(CGame::GetInstance()->GetJsyInputHandle(), JSY_INPUT_DOWN, &keyDown);
	JsyInputGetInput(CGame::GetInstance()->GetJsyInputHandle(), JSY_INPUT_A, &keyShoot);
    JsyInputGetInput(CGame::GetInstance()->GetJsyInputHandle(), JSY_INPUT_B, &keyFrameRatio);

	// Check vertical movement
	if ((keyUp > 0.0f))
	{
		mVelocity.y = MOVE_FORCE;
	}
	else if ((keyDown > 0.0f))
	{
		mVelocity.y = -MOVE_FORCE;
	}
	else
	{
		mVelocity.y = 0.0f;
	}

	// Check horizontal movement
	if ((keyLeft > 0.0f))
	{
		mVelocity.x = -MOVE_FORCE;
		mIsFacingLeft = true;
	}
	else if ((keyRight > 0.0f))
	{
		mVelocity.x = MOVE_FORCE;
		mIsFacingLeft = false;
	}
	else
	{
		mVelocity.x = 0.0f;
	}

	// Check for firing missles
	if (mCanShoot && (keyShoot > 0.0f)) {
		mCanShoot = false;
		mShotTimer = 0;
		Shoot();
		if (mFireSFXId != 0) {
            JsyAudioPlaySound(CGame::GetInstance()->GetJsyAudioHandle(), mFireSFXId);
		}
	}

    if (keyFrameRatio > 0.0f) {
        if (!bulletTimeDebounce) {
            bulletTimeDebounce = true;
            if (inBulletTime) {
                inBulletTime = false;
                CGame::GetInstance()->setFrameRatio(1.0f);
            }
            else {
                if (bulletTime > 0.5f) {
                    inBulletTime = true;
                    CGame::GetInstance()->setFrameRatio(PLAYER_BULLETTIME_RATIO);
                }
            }
        }
    }

    if (keyFrameRatio < 0.1f) {
        bulletTimeDebounce = false;
    }
}

void Player::Shoot() {
	float_t spreadAngle;
	Bullet* homingBullet;
	switch (currentWeapon) {
	case NORMAL:
		SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, 0.0f, SHOT_FORCE, SpriteManager::PLAYER);
		break;
	case QUICK:
		SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, 0.0f, QUICK_SHOT_FORCE, SpriteManager::PLAYER);
		break;
	case SPREAD:
		spreadAngle = atanf(SPREAD_SHOT_ANGLE / SPREAD_SHOT_FORCE);
		SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, -spreadAngle, SPREAD_SHOT_FORCE, SpriteManager::PLAYER);
		SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, 0.0f, SPREAD_SHOT_FORCE, SpriteManager::PLAYER);
		SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, spreadAngle, SPREAD_SHOT_FORCE, SpriteManager::PLAYER);
		break;
	case HOMING:
		homingBullet = SpriteManager::GetInstance()->CreateBullet(getPosition()->x, getPosition()->y, 0.0f, HOMING_FORCE, SpriteManager::PLAYER);
		homingBullet->homingMissile = true;
		break;
	default:
		break;

	}
}

void Player::CheckBoundaries()
{
	FieldC *field = FieldManagerC::GetInstance()->getFieldPtr();

	float_t rightSide = field->getPosition()->x + ((float_t)field->getWidth() / 2.0f);
	float_t leftSide = field->getPosition()->x - ((float_t)field->getWidth() / 2.0f);
	float_t topSide = field->getPosition()->y - ((float_t)field->getHeight() / 2.0f);
	float_t bottomSide = field->getPosition()->y + ((float_t)field->getHeight() / 2.0f);

	if (mPosition.x - mWidth / 2 <= leftSide)
	{
		mPosition.x = leftSide + mWidth / 2;
	}
	if (mPosition.x + mWidth / 2 >= rightSide)
	{
		mPosition.x = rightSide - mWidth / 2;
	}
	if (mPosition.y + mHeight / 2 >= bottomSide)
	{
		mPosition.y = bottomSide - mHeight / 2;
	}
	if (mPosition.y - mHeight / 2 <= topSide)
	{
		mPosition.y = topSide + mHeight / 2;
	}
}

void Player::DrawLivesLeft()
{
	for (int32_t i = 0; i < mNumLives; i++)
	{
		mLives[i]->render();
	}
}

void Player::ChangeWeapon(int32_t newWeapon) 
{
	mPowerupTimer = WEAPON_DURATION_MS;
	currentWeapon = newWeapon;
}

