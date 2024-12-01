#include "game/Ship.hpp"
#include "RuneEngine/variables.hpp"
#include "game/AbstractShip.hpp"

Ship::Ship()
	: AbstractShip(*texture)
{
}

void Ship::rotation()
{
	using namespace rn::math;
	Direction dir{ rn::Vec2f(rn::mouse_position) - getPosition() };
	setDirection(dir.x, dir.y);
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
			d_move = std::make_unique<Direction>(-getDirection());
		else
			*d_move -= getDirection();
	}
	if (rn::isKeyhold(sf::Keyboard::A))
	{
		if (!d_move)
			d_move = std::make_unique<Direction>(nor(getDirection()));
		else
			*d_move += nor(getDirection());
	}
	if (rn::isKeyhold(sf::Keyboard::D))
	{
		if (!d_move)
			d_move = std::make_unique<Direction>(-nor(getDirection()));
		else
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
void Ship::onEvent(sf::Event &event)
{
	AbstractShip::onEvent(event);
	if (rn::isKeydown(sf::Mouse::Left))
	{
		shoot();
	}
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
}
AbstractShip *Ship::copy() const
{
	return new Ship();
}
