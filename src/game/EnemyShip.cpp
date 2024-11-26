#include "game/EnemyShip.hpp"
#include "game/AbstractShip.hpp"


EnemyShip::EnemyShip()
	: AbstractShip(*texture)
{}


void EnemyShip::onMove()
{
	AbstractShip::onMove();
	updateCollider();
}
void EnemyShip::onHit()
{
	AbstractShip::onHit();
}

AbstractShip *EnemyShip::copy() const
{
	return new EnemyShip();
}