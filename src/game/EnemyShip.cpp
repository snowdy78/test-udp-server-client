#include "game/EnemyShip.hpp"
#include "game/AbstractShip.hpp"
#include "game/Bullet.hpp"


EnemyShip::EnemyShip()
	: AbstractShip(*texture)
{}


void EnemyShip::onMove()
{
	AbstractShip::onMove();
	updateCollider();
}
void EnemyShip::update()
{
	updateCollisionState();
}
