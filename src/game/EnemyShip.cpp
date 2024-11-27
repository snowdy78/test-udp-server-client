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
	AbstractShip::rotation();
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
		setDirection(rn::math::norm(nearest - getPosition()));
		setRotation(rn::math::rot(nearest - getPosition()));
	}
}
void EnemyShip::movement()
{
	AbstractShip::movement();
	if (static_cast<int>(clock.getElapsedTime().asSeconds()) % 2 == 0)
	{
		randomly_move = nullptr;
	}
	if (static_cast<int>(clock.getElapsedTime().asSeconds()) % 3 == 1)
	{
		if (!randomly_move)
		{
			randomly_move.reset(new int(rn::random::integer(0, 1)));
		}
		move(*randomly_move * getVelocity() * getDirection());
	}
	if (static_cast<int>(clock.getElapsedTime().asMilliseconds()) % 1000 > 500)
	{
		if (!randomly_move)
		{
			randomly_move.reset(new int(rn::random::integer(0, 1)));
		}
		move(*randomly_move * getVelocity() * rn::math::nor(getDirection()));
	}
}

void EnemyShip::update()
{
	AbstractShip::update();
	if (static_cast<int>(clock.getElapsedTime().asSeconds()) % 2 == 1)
	{
		ready_to_shoot = true;
	}
	else if (static_cast<int>(clock.getElapsedTime().asMilliseconds()) % 1000 > 500 && ready_to_shoot)
	{
		shoot();
		ready_to_shoot = false;
	}
}
