#include "game/Ship.hpp"
#include "game/Gun.hpp"

Ship::Ship() : RigitBody2d(*texture) {}
void Ship::shoot()
{
	if (!gun)
	{
		return;
	}
	gun->shoot(getDirection2d());
}
void Ship::setGun(const Gun &gun)
{
	if (this->gun)
		delete this->gun;
	this->gun = gun.copy();
}
Ship::~Ship()
{
	delete gun;
}
Ship &Ship::operator=(const Ship &ship)
{
	if (this != &ship)
	{
		delete gun;
		gun = ship.gun->copy();
	}
	return *this;
}
Ship &Ship::operator=(Ship &&ship) noexcept
{
	if (this != &ship)
	{
		delete gun;
		gun		 = ship.gun;
		ship.gun = nullptr;
	}
	return *this;
}
Ship::Ship(const Ship &ship) : RigitBody2d(*texture), gun(ship.gun->copy()) {}
Ship::Ship(Ship &&ship) noexcept : RigitBody2d(*texture)
{
	gun		 = ship.gun;
	ship.gun = nullptr;
}
void Ship::update()
{
	RigitBody2d::update();
	if (gun)
	{
		gun->update();
	}
}
void Ship::onEvent(sf::Event &event)
{
	RigitBody2d::onEvent(event);
	if (gun)
	{
		gun->onEvent(event);
	}
	if (rn::isKeydown(sf::Mouse::Left))
	{
		shoot();
	}
}
void Ship::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
	if (gun)
		target.draw(*gun);
}
void Ship::setPosition(float x, float y)
{
	sf::Transformable::setPosition(x, y);
	gun->setPosition(x, y);
}
void Ship::setPosition(const rn::Vec2f &vector)
{
	sf::Transformable::setPosition(vector);
	gun->setPosition(vector);
}
