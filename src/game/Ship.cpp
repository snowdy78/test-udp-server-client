#include "game/Ship.hpp"
#include "game/AbstractShip.hpp"
#include "game/Bullet.hpp"

Ship::Ship()
	: AbstractShip(*texture)
{}

void Ship::rotation()
{
	using namespace rn::math;
	setRotation(rot(getDirection()));
}

void Ship::movement()
{
	using namespace rn::math;
	std::unique_ptr<Direction> d_move = nullptr;
	if (rn::isKeyhold(sf::Keyboard::W))
	{
		d_move = std::make_unique<Direction>(getDirection());
	}
	if (rn::isKeyhold(sf::Keyboard::S))
	{
		if (!d_move)
		{
			d_move = std::make_unique<Direction>(-getDirection());
		}
		*d_move -= getDirection();
	}
	if (rn::isKeyhold(sf::Keyboard::A))
	{
		if (!d_move)
		{
			d_move = std::make_unique<Direction>(nor(getDirection()));
		}
		*d_move += nor(getDirection());
	}
	if (rn::isKeyhold(sf::Keyboard::D))
	{
		if (!d_move)
		{
			d_move = std::make_unique<Direction>(-nor(getDirection()));
		}
		*d_move -= nor(getDirection());
	}
	if (d_move)
	{
		move(getVelocity() * d_move->x, getVelocity() * d_move->y);
	}
}

void Ship::onMove()
{
	sf::Listener::setPosition(getPosition().x, getPosition().y, 0);
	rn::Vec2f perp = rn::math::nor(getPosition());
	sf::Listener::setUpVector(perp.x, perp.y, 0.f);
	AbstractShip::onMove();
	updateCollider();
}
void Ship::onRotation()
{
	sf::Listener::setDirection({ getDirection().x, getDirection().y, 0.f });
	AbstractShip::onRotation();
	updateCollider();
}
void Ship::onHit() 
{
	AbstractShip::onHit();
	std::cout << "I'm a ship!\n"; // TODO: remove
}
