#ifndef _ET_H
#define _ET_H

#include "Sprite.h"
#include "gamedefs.h"

class Player : public Sprite
{
public:

    // Factory function
    static Player* CreatePlayer(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, int32_t gameObjectType);
	~Player();

    void update(uint32_t milliseconds);
	void updateET(uint32_t milliseconds);
	void playerHit();
	void AddExtraLife();
	void DrawLivesLeft();

	void ChangeWeapon(int32_t newWeapon);
	bool8_t IsInvincible();
	void EnableInvincible();

    void setFireSfxId(uint32_t fireSFXId) { mFireSFXId = fireSFXId; };
	enum WEAPON_TYPES 
	{
		NORMAL,
		QUICK,
		SPREAD,
		HOMING
	};

private:
    Player(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, int32_t gameObjectType);

    bool bulletTimeDebounce;
    float_t bulletTime;
    bool inBulletTime;
	bool8_t mIsMoving;
	bool8_t mCanMove;
	bool8_t mCanShoot;
	
	int32_t MInvincibleTimer;
	bool8_t mInvincible;

	int32_t mNumLives;

	int32_t currentWeapon;
	int32_t mPowerupTimer;

	float_t mMoveForce;
    int32_t mShotTimer;

    uint32_t mFireSFXId;
    uint32_t mHitSFXId;
	Sprite* mLives[MAX_PLAYER_LIVES];

	void CheckForUserInput();
	void CheckBoundaries();
	void Shoot();
};

#endif