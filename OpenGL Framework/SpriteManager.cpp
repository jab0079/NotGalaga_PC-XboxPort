#define SPRITE_MANAGER_CPP
#include <assert.h>
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <float.h>
#include <malloc.h>
#include "jsy/jsy.h"

#include "jsy/jsy.h"	
#include "gamedefs.h"
#include "collinfo.h"
#include "object.h"
#include "Sprite.h"
#include "Player.h"
#include "Bullet.h"
#include "random.h"
#include "field.h"
#include "FieldManager.h"
#include "stateManager.h"
#include "SpriteManager.h"
#include "random.h"
#include "GameManager.h"
#include "FallTrajectory.h"
#include "FollowTrajectory.h"
#include "SideTrajectory.h"
#include "game.h"

SpriteManager* SpriteManager::sInstance = NULL;

static const int32_t points[SpriteManager::POINTS_NONE] = { 150, 500, 800, 1000, 1500, 1600, 2000, 3000 };

SpriteManager *SpriteManager::CreateInstance()
{
	assert(sInstance == NULL);
	sInstance = new SpriteManager();
	return sInstance;
}

SpriteManager::SpriteManager(){
	//moved from .h
player = nullptr;
for(int i = 0; i < MAX_NUM_MISSILES; i++){
	bullets[i] = nullptr;
}
for(int i = 0; i < ENEMY_MAX_ENEMIES; i++){
	enemies[i] = nullptr;
}
for(int i = 0; i < MAX_EXPLOSIONS; i++){
	explosions[i] = nullptr;
}
for(int i = 0; i < MAX_WEAPON_DROPS; i++){
	weaponDrops[i] = nullptr;
}
gameOver = nullptr;
}

SpriteManager::~SpriteManager() {
	for (int i = 0; i < ENEMY_MAX_ENEMIES; i++) {
		if (enemies[i] != nullptr) {
			delete enemies[i];
		}
	}
}

void SpriteManager::init()
{
	printf("Initing the SpriteManager.\n");

	spriteTextureMaps = (uint32_t*)malloc(NUM_OBJECTS * sizeof(uint32_t));

    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), PLAYER_SPRITE, &spriteTextureMaps[PLAYER]);
    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), ENEMY_SPRITE_GREEN, &spriteTextureMaps[ENEMY_GREEN]);
    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), ENEMY_SPRITE_PURPLE, &spriteTextureMaps[ENEMY_PURPLE]);
    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), ENEMY_SPRITE_RED, &spriteTextureMaps[ENEMY_RED]);
    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), ENEMY_SPRITE_YELLOW, &spriteTextureMaps[ENEMY_YELLOW]);
	JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), ENEMY_SPRITE_SHIP, &spriteTextureMaps[ENEMY_SHIP]);
    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), MISSILE_SPRITE, &spriteTextureMaps[BULLET]);
	JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), FAST_SHOT_WEAPON, &spriteTextureMaps[QUICK_WEAPON]);
	JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), SPREAD_SHOT_WEAPON, &spriteTextureMaps[SPREAD_WEAPON]);
	JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), HOMING_SHOT_WEAPON, &spriteTextureMaps[HOMING_WEAPON]);
    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), EXPLOSION_PLAYER_SPRITE, &spriteTextureMaps[EXPLOSION_PLAYER]);
    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), EXPLOSION_ENEMY_SPRITE, &spriteTextureMaps[EXPLOSION_ENEMY]);
    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), POINTS_SPRITES, &spriteTextureMaps[POINTS]);
    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), GAMEOVER_SPRITE, &spriteTextureMaps[GAMEOVER]);
    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), HORIZONTAL_LINE, &spriteTextureMaps[HLINE]);
    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), VERTICAL_LINE, &spriteTextureMaps[VLINE]);
    JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), HIGH_SCORE_SPRITE, &spriteTextureMaps[LABEL]);
	JStGLoadTexture(CGame::GetInstance()->GetJsyGHandle(), NUMBER_SPRITES, &spriteTextureMaps[NUMBERS]);

	mInGame = false;
}

void SpriteManager::updateSprites(uint32_t milliseconds)
{
	if (!mInGame)
	{
		return;
	}

	// Update player
	player->update(milliseconds);
	player->updateET(milliseconds);

	// Update other sprites
	for (int i = 0; i < MAX_NUM_MISSILES; i++) 
	{
		if (bullets[i] != nullptr)
		{
			bullets[i]->update(milliseconds);
			bullets[i]->UpdateBullet(milliseconds);
		}
	}

	for (int i = 0; i < ENEMY_MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->update(milliseconds);
		}
	}

	for (int i = 0; i < MAX_WEAPON_DROPS; i++)
	{
		if (weaponDrops[i] != nullptr)
		{
			weaponDrops[i]->update(milliseconds);
		}
	}

	for (int i = 0; i < MAX_EXPLOSIONS; i++)
	{
		if (explosions[i] != nullptr)
		{
			if (explosions[i]->CycleExplosionAnimation(milliseconds))
			{
				delete explosions[i];
				explosions[i] = nullptr;
			}
		}
	}

	// Collision checks
	CheckBoundaryCollisions();
	CheckBulletCollisions();
	CheckWeaponDropCollisions();
}

Enemy* SpriteManager::GetNearestEnemy(Sprite* origin) {
	Enemy* nearestEnemy = nullptr;
	float_t nearestDistance = FLT_MAX;
	for (int i = 0; i < ENEMY_MAX_ENEMIES; i++) {
		if (enemies[i] == nullptr) {
			continue;
		}
		float_t distance = GetHeuristicDistance(player, enemies[i]) < nearestDistance;
		if (distance < nearestDistance) {
			nearestEnemy = enemies[i];
			nearestDistance = distance;
		}
	}
	return nearestEnemy;
}

float_t SpriteManager::GetHeuristicDistance(Sprite* origin, Sprite* destination) {
	return powf(origin->getPosition()->x - destination->getPosition()->x, 2) + powf(origin->getPosition()->y - destination->getPosition()->y, 2);
}

void SpriteManager::renderSprites()
{
	if (gameOver != nullptr)
	{
		gameOver->render();
	}

	if (!mInGame)
	{
		return;
	}

	if (player != nullptr)
	{
		player->render();
		player->DrawLivesLeft();
	}

	for (int i = 0; i < ENEMY_MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->render();
		}
	}

	for (int i = 0; i < MAX_NUM_MISSILES; i++)
	{
		if (bullets[i] != nullptr)
		{
			bullets[i]->render();
		}
	}

	for (int i = 0; i < MAX_WEAPON_DROPS; i++)
	{
		if (weaponDrops[i] != nullptr)
		{
			weaponDrops[i]->render();
		}
	}

	for (int i = 0; i < MAX_EXPLOSIONS; i++)
	{
		if (explosions[i] != nullptr)
		{
			explosions[i]->render();
		}
	}
}

uint32_t SpriteManager::getSpriteTextureMap(int32_t objectType)
{
	return spriteTextureMaps[objectType];
}

void SpriteManager::shutdown()
{
	resetGame();

	free(spriteTextureMaps);

	for (int32_t i = 0; i < MAX_NUM_MISSILES; i++)
	{
		if (bullets[i] != nullptr) {
			delete bullets[i];
			bullets[i] = nullptr;
		}
	}

	for (int32_t i = 0; i < ENEMY_MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr) {
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	for (int32_t i = 0; i < MAX_WEAPON_DROPS; i++)
	{
		if (weaponDrops[i] != nullptr) {
			delete weaponDrops[i];
			weaponDrops[i] = nullptr;
		}
	}

	for (int i = 0; i < MAX_EXPLOSIONS; i++)
	{
		if (explosions[i] != nullptr) {
			delete explosions[i];
			explosions[i] = nullptr;
		}
	}
}

void SpriteManager::resetGame()
{
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}

	if (gameOver != nullptr)
	{
		delete gameOver;
		gameOver = nullptr;
	}

	for (int i = 0; i < MAX_NUM_MISSILES; i++)
	{
		if (bullets[i] != nullptr)
		{
			delete bullets[i];
			bullets[i] = nullptr;
		}
	}

	for (int i = 0; i < MAX_WEAPON_DROPS; i++)
	{
		if (weaponDrops[i] != nullptr)
		{
			delete weaponDrops[i];
			weaponDrops[i] = nullptr;
		}
	}

	for (int i = 0; i < ENEMY_MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	for (int i = 0; i < MAX_EXPLOSIONS; i++)
	{
		if (explosions[i] != nullptr)
		{
			delete explosions[i];
			explosions[i] = nullptr;
		}
	}
}

void SpriteManager::startGame()
{
	static uint32_t id = JsyAudioLoad(CGame::GetInstance()->GetJsyAudioHandle(), START_SFX);
    JsyAudioPlaySound(CGame::GetInstance()->GetJsyAudioHandle(), id);
	resetGame();
	player = Player::CreatePlayer(0.0f, 0.0f, 0.0f, 0.0f, PLAYER);
	mInGame = true;
}

void SpriteManager::endGame()
{
	gameOver = new Sprite(0.0f, 0.0f, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, GAMEOVER);
	mInGame = false;
	GameManager::GetInstance()->setState(GameManager::GAME_OVER);
}

Bullet* SpriteManager::CreateBullet(float_t x, float_t y, float_t xVel, float_t yVel, int32_t ownerType)
{
	for (int i = 0; i < MAX_NUM_MISSILES; i++)
	{
		if (bullets[i] == nullptr) {
			bullets[i] = new Bullet(x, y, xVel, yVel, BULLET, ownerType);
			return bullets[i];
		}
	}
	return nullptr;
}

void SpriteManager::CreateWeaponDrop(float_t x, float_t y, float_t xVel, float_t yVel, int32_t weaponType) {
	for (int i = 0; i < MAX_WEAPON_DROPS; i++)
	{
		if (weaponDrops[i] == nullptr)
		{
			bool quickOne = Player::QUICK == weaponType;
			bool spreadOne = Player::SPREAD == weaponType;
			bool homingOne = Player::HOMING == weaponType;
			int32_t weaponOne  = -1;
			if (quickOne) {
				weaponOne = QUICK_WEAPON;
			}
			else if (spreadOne) {
				weaponOne = SPREAD_WEAPON;
			}
			else if (homingOne) {
				weaponOne = HOMING_WEAPON;
			}
			if (weaponOne >= 0) {
				weaponDrops[i] = new WeaponDrop(x, y, xVel, yVel, weaponOne, weaponType);
			}

			/*int32_t weaponObj = QUICK_WEAPON + weaponType - 1;
			if (weaponObj >= 0)
			{
				weaponDrops[i] = new WeaponDrop(x, y, xVel, yVel, weaponObj, weaponType);
			}*/
		}
	}
}

void SpriteManager::CreateExplosion(float_t x, float_t y, uint32_t explosionType, uint32_t pointType)
{
	for (int i = 0; i < MAX_EXPLOSIONS; i++)
	{
		if (explosions[i] == nullptr)
		{
			explosions[i] = new Explosion(x, y, explosionType, pointType);
			break;
		}
	}
}

void SpriteManager::CheckBoundaryCollisions()
{
	// Destroy bullets that go offscreen
	for (int32_t i = 0; i < MAX_NUM_MISSILES; i++)
	{
		if (bullets[i] != nullptr && CheckSpriteHitBoundaries(bullets[i]))
		{
			delete bullets[i];
			bullets[i] = nullptr;
		}
	}

	for (int32_t i = 0; i < MAX_WEAPON_DROPS; i++)
	{
		if (weaponDrops[i] != nullptr && CheckSpriteHitBoundaries(weaponDrops[i]))
		{
			delete weaponDrops[i];
			weaponDrops[i] = nullptr;
		}
	}
}

void SpriteManager::CheckWeaponDropCollisions() {
	for (int32_t i = 0; i < MAX_WEAPON_DROPS; i++)
	{
		if (weaponDrops[i] != nullptr && CheckSpriteCollision(weaponDrops[i], player))
		{
			player->ChangeWeapon(weaponDrops[i]->GetWeaponType());
			delete weaponDrops[i];
			weaponDrops[i] = nullptr;
		}
	}
}

void SpriteManager::CheckBulletCollisions()
{
	for (int32_t i = 0; i < MAX_NUM_MISSILES; i++)
	{
		if (bullets[i] != nullptr)
		{
			// Check who fired the bullet to determine who it should hit
			if (bullets[i]->GetOwnerType() == PLAYER)
			{

				// Check if missile fired by player has hit an enemy, then destroy both enemy and bullet
				// Also, increment player score and start explosion animation			
				for (int32_t j = 0; j < ENEMY_MAX_ENEMIES; j++)
				{
					if (enemies[j] != nullptr)
					{
						if (CheckSpriteCollision(bullets[i], enemies[j]))
						{
							CreateExplosion(enemies[j]->getPosition()->x, enemies[j]->getPosition()->y, EXPLOSION_ENEMY, enemies[j]->getType());
							if (enemies[j]->hit())
							{
								if (enemies[j]->getType() == ENEMY_SHIP)
								{
									player->AddExtraLife();
								}
								GameManager::GetInstance()->enemyKilled(points[enemies[j]->getType()]);
								delete enemies[j];
								enemies[j] = nullptr;
							}

							delete bullets[i];
							bullets[i] = nullptr;							
							break;
						}
					}
				}
			}
			else
			{

				// Check if missile fired by enemy has hit the player, then destroy bullet and decrement player lives
				// Also, increment player score and start explosion animation
				if (CheckSpriteCollision(player, bullets[i]) && !player->IsInvincible())
				{
					player->EnableInvincible();
					CreateExplosion(player->getPosition()->x, player->getPosition()->y, EXPLOSION_PLAYER, POINTS_NONE);
					player->playerHit();

					delete bullets[i];
					bullets[i] = nullptr;
					break;
				}
			}
		}
	}
}


void SpriteManager::spawnEnemy(uint32_t indexEnemy) {
    if (enemies[indexEnemy] == nullptr) {
        static uint32_t id = JsyAudioLoad(CGame::GetInstance()->GetJsyAudioHandle(), ENEMY_SFX_KILL);
		
		// Choose random enemy type
		int32_t type = 0;
		if (indexEnemy == SHIP_SPAWN)
		{
			type = ENEMY_SHIP;
		}
		else
		{
			type = getRangedRandom(ENEMY_GREEN, ENEMY_YELLOW);
		}
		enemies[indexEnemy] = new Enemy(type);

		// Set trajectory & sfx
        Trajectory * trajectory = NULL;
		if (type == ENEMY_SHIP)
			trajectory = new FollowTrajectory(enemies[indexEnemy]);
        else if ((type == ENEMY_YELLOW) || (type == ENEMY_RED))
			trajectory = new FallTrajectory(enemies[indexEnemy]);
		else
			trajectory = new SideTrajectory(enemies[indexEnemy]);

		enemies[indexEnemy]->setKillSfxId(id);
		enemies[indexEnemy]->setTrajectory(trajectory);

		// Set random spawn position
		float_t bgWidth = (float_t)GameManager::GetInstance()->getBackgroundWidth() - enemies[indexEnemy]->getWidth();
		float_t bgHeight = (float_t)GameManager::GetInstance()->getBackgroundHeight() - enemies[indexEnemy]->getHeight();
		enemies[indexEnemy]->setPosition(getRangedRandom(-bgWidth / 3.0f, bgWidth / 3.0f), getRangedRandom(bgHeight / 4.0f, (bgHeight / 2.0f) - ENEMY_HEIGHT));
		enemies[indexEnemy]->reset();
	}
}

bool8_t SpriteManager::CheckSpriteHitBoundaries(Sprite *sprite)
{
	// Check if sprite is out of bounds 

	FieldC *field = FieldManagerC::GetInstance()->getFieldPtr();
	float_t leftSide = field->getPosition()->x - ((float_t)field->getWidth() / 2.0f);
	float_t rightSide = field->getPosition()->x + ((float_t)field->getWidth() / 2.0f);
	float_t topSide = field->getPosition()->y - ((float_t)field->getHeight() / 2.0f);
	float_t bottomSide = field->getPosition()->y + ((float_t)field->getHeight() / 2.0f);

	float_t spriteLeft = sprite->getPosition()->x - sprite->getWidth() / 2;
	float_t spriteRight = sprite->getPosition()->x + sprite->getWidth() / 2;
	float_t spriteUp = sprite->getPosition()->y - sprite->getHeight() / 2;
	float_t spriteDown = sprite->getPosition()->y + sprite->getHeight() / 2;

	if ((spriteUp >= bottomSide) || (spriteDown <= topSide))
	{
		field = FieldManagerC::GetInstance()->getFieldPtr();
	}

	return	(spriteLeft <= leftSide) || (spriteRight >= rightSide) ||
		(spriteUp >= bottomSide) || (spriteDown <= topSide);
}

bool8_t SpriteManager::CheckSpriteCollision(Sprite *sprite1, Sprite *sprite2)
{
	// Check if sprites are colliding

	float_t sprite1Left = sprite1->getPosition()->x - sprite1->getWidth() / 2;
	float_t sprite1Right = sprite1->getPosition()->x + sprite1->getWidth() / 2;
	float_t sprite1Up = sprite1->getPosition()->y - sprite1->getHeight() / 2;
	float_t sprite1Down = sprite1->getPosition()->y + sprite1->getHeight() / 2;

	float_t sprite2Left = sprite2->getPosition()->x - sprite2->getWidth() / 2;
	float_t sprite2Right = sprite2->getPosition()->x + sprite2->getWidth() / 2;
	float_t sprite2Up = sprite2->getPosition()->y - sprite2->getHeight() / 2;
	float_t sprite2Down = sprite2->getPosition()->y + sprite2->getHeight() / 2;

	return	(sprite1Left <= sprite2Right) && (sprite1Right >= sprite2Left) &&
		(sprite1Up <= sprite2Down) && (sprite1Down >= sprite2Up);
}
