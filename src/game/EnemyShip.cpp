#include "game/EnemyShip.hpp"
#include "game/AbstractShip.hpp"

EnemyShip::EnemyShip() : AbstractShip(*texture) {}

bool EnemyShip::resolve(const Collidable *collidable) const
{
	return dynamic_cast<const Bullet *>(collidable);
}

const Collider *EnemyShip::getCollider() const
{
	return &collider;
}

void EnemyShip::updateCollider()
{
	rn::math::rectangle rect{ getGlobalBounds() };
	collider.transform(rect);
}
void EnemyShip::onMove()
{
	AbstractShip::onMove();
	updateCollider();
}
