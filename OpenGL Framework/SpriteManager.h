#ifndef _SPRITE_MANAGER_H
#define _SPRITE_MANAGER_H

#include "Player.h"
#include "Bullet.h"
#include "gamedefs.h"
#include "jsy/jsy.h"
#include "Enemy.h"
#include "Explosion.h"
#include "WeaponDrop.h"

class SpriteManager
{
public:
	enum GAME_OBJECTS
	{
		ENEMY_GREEN,	// 150pts
		ENEMY_PURPLE,	// 500pts
		ENEMY_RED,		// 800pts
		ENEMY_YELLOW,	// 1000pts
		ENEMY_SHIP,		// 1500pts
		PLAYER,
		BULLET,
		QUICK_WEAPON,
		SPREAD_WEAPON,
		HOMING_WEAPON,
		EXPLOSION_PLAYER,
		EXPLOSION_ENEMY,
		POINTS,
		GAMEOVER,
		HLINE,
		VLINE,
		LABEL,
		NUMBERS,
		NUM_OBJECTS
	};

	enum POINT_TYPES
	{
		POINTS_150,
		POINTS_500,
		POINTS_800,
		POINTS_1000,
		POINTS_1500,
		POINTS_1600,
		POINTS_2000,
		POINTS_3000,
		POINTS_NONE
	};


	static SpriteManager *CreateInstance();
	static SpriteManager *GetInstance() { return sInstance; };
	~SpriteManager();

	void	init();
	void	shutdown();
	void	updateSprites(uint32_t milliseconds);
	void	renderSprites();
    uint32_t getSpriteTextureMap(int32_t objectType);
	void	resetGame();
	void	startGame();
	void	endGame();
	void	spawnEnemy(uint32_t indexEnemy);


	Player* getET() { return player; }
	Bullet* CreateBullet(float_t x, float_t y, float_t xVel, float_t yVel, int32_t ownerType);
	void CreateWeaponDrop(float_t x, float_t y, float_t xVel, float_t yVel, int32_t weaponType);
	void CreateExplosion(float_t x, float_t y, uint32_t explosionType, uint32_t pointType);
	Enemy* GetNearestEnemy(Sprite* origin);

private:
	SpriteManager();
	static SpriteManager *sInstance;

    uint32_t *spriteTextureMaps;
	bool8_t mInGame;

	// GameObjects
	Player* player;
	Bullet* bullets[MAX_NUM_MISSILES];
    Enemy* enemies[ENEMY_MAX_ENEMIES];
	Explosion* explosions[MAX_EXPLOSIONS];
	WeaponDrop* weaponDrops[MAX_WEAPON_DROPS];
	Sprite* gameOver;

	// Collsions
	void CheckBoundaryCollisions();
	void CheckWeaponDropCollisions();
	void CheckBulletCollisions();
	bool8_t CheckSpriteHitBoundaries(Sprite *sprite);
	bool8_t CheckSpriteCollision(Sprite *sprite1, Sprite *sprite2);

	float_t GetHeuristicDistance(Sprite* origin, Sprite* destination);
};

#endif
