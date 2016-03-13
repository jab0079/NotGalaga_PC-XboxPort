#include "object.h"
#include "Sprite.h"
#include "field.h"

#include "FollowTrajectory.h"

FollowTrajectory::FollowTrajectory(Sprite* sprite)
{
	mSprite = sprite;
	mPosition = *mSprite->getPosition();
}


FollowTrajectory::~FollowTrajectory()
{}

void FollowTrajectory::update(uint32_t milliseconds)
{
	Player *player = SpriteManager::GetInstance()->getET();

	mPosition.x = player->getPosition()->x;
}
