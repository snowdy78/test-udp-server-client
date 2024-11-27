#include "game/EnemyShip.hpp"
#include "game/AbstractShip.hpp"
#include "game/SpaceField.hpp"

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
void EnemyShip::rotation()
{
	if (field)
	{
		rn::math::point_array points;
		for (auto &ship: *field)
		{
			if (ship != this)
				points.push_back(ship->getPosition());
		}
		if (points.empty())
			return;
		rn::math::intersection_t arr{ points.begin(), points.end() };
		rn::Vec2f nearest = arr.nearest(getPosition());
		setRotation(rn::math::rot(nearest - getPosition()));
	}
}
void EnemyShip::movement() {}
