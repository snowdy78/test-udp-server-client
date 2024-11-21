#include "game/EnemyShip.hpp"
#include "game/AbstractShip.hpp"
#include "game/Bullet.hpp"


EnemyShip::EnemyShip() : AbstractShip(*texture) {}

bool EnemyShip::resolve(const Collidable *collidable) const
{
	return dynamic_cast<const Bullet *>(collidable);
}

void EnemyShip::onMove()
{
	AbstractShip::onMove();
	updateCollider();
}
void EnemyShip::update()
{
	updateCollisionState();
}
