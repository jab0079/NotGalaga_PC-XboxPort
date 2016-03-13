#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "jsy/jsy.h"
#include "Sprite.h"
#include "Trajectory.h"

class Enemy : public Sprite
{
public:
    Enemy(uint32_t type);
    ~Enemy();

    void update(uint32_t milliseconds);
    void setSpriteType(int32_t type);
    void setPosition(float x, float y);
	void setTrajectory(Trajectory* newTrajectory);
    void setKillSfxId(uint32_t killSFXId) { mKillSFXId = killSFXId; };
    void reset();
	bool8_t hit();

private:
    Trajectory* mTrajectory;
    uint32_t lastShootDuration;

    uint32_t mKillSFXId;
	int32_t mHealth;
	bool8_t mIsDead;
};


#endif