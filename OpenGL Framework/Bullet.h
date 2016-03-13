#ifndef _BULLET_H
#define _BULLET_H

#include "Sprite.h"

class Bullet : public Sprite
{

public:
	Bullet(float_t x, float_t y, float_t xVel, float_t yVel, int32_t objectType, int32_t ownerType);
	~Bullet();
	
	int32_t GetOwnerType() { return mOwnerType; }
	void UpdateBullet(uint32_t milliseconds);
	bool homingMissile;

private:
	int32_t mOwnerType;

};

#endif