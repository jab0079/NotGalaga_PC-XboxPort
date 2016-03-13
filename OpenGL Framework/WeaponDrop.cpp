#ifndef _WEAPONDROP_MANAGER_H
#define _WEAPONDROP_MANAGER_H

#include "WeaponDrop.h"
#include "gamedefs.h"




WeaponDrop::WeaponDrop(float_t x, float_t y, float_t xVel, float_t yVel, int32_t objectType, int32_t weaponType)
{
	// Object
	mPosition.x = x;
	mPosition.y = y;
	mVelocity.x = xVel;
	mVelocity.y = yVel;
	mCollInfo.shape = CollInfoC::SHAPE_RECTANGLE;

	// Sprite
	mWidth = WEAPON_DROP_WIDTH;
	mHeight = WEAPON_DROP_HEIGHT;
	mNumSprites = WEAPON_DROP_NUM_SPRITES;
	mCurrentSprite = 0;

	mType = objectType;

	mEnabled = true;
	mIsFacingLeft = false;

	// Bullet
	mWeaponType = weaponType;
}


WeaponDrop::~WeaponDrop()
{
}
void WeaponDrop::UpdateWeaponDrop(uint32_t milliseconds) {

}

#endif
