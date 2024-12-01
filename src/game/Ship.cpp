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
		rn::Vec2f value{0.0, -1.0};
		d_move = std::make_unique<Direction>(value);
	}
	if (rn::isKeyhold(sf::Keyboard::S))
	{
		rn::Vec2f value{0.0, 1.0};
		if (!d_move)
			d_move = std::make_unique<Direction>(value);
		else
			*d_move += value;
	}
	if (rn::isKeyhold(sf::Keyboard::A))
	{
		rn::Vec2f value{-1.0, 0.0};
		if (!d_move)
			d_move = std::make_unique<Direction>(value);
		else
			*d_move += value;
	}
	if (rn::isKeyhold(sf::Keyboard::D))
	{
		rn::Vec2f value{1.0, 0.0};
		if (!d_move)
			d_move = std::make_unique<Direction>(value);
		else
			*d_move += value;
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
