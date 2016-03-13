#ifndef _WEAPONDROP_H
#define _WEAPONDROP_H

#include "Sprite.h"

class WeaponDrop : public Sprite
{

public:
	WeaponDrop(float_t x, float_t y, float_t xVel, float_t yVel, int32_t objectType, int32_t weaponType);
	~WeaponDrop();

	int32_t GetWeaponType() { return mWeaponType; }
	void UpdateWeaponDrop(uint32_t milliseconds);

private:
	int32_t mWeaponType;

};

#endif