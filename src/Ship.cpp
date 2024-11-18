#include "Ship.hpp"
#include "Gun.hpp"

Ship::Ship() : RigitBody2d(*texture)
{}
void Ship::shoot()
{
	if (!gun)
	{
		return;
	}
	gun->shoot(RigitBody2d::getDirection2d());
}
void Ship::setGun(const Gun &gun)
{
	delete this->gun;
	this->gun = gun.copy();
}
Ship::~Ship()
{
	delete gun;
}
Ship &Ship::operator=(const Ship &ship) {
	if (this != &ship)
	{
		delete gun;
		gun = ship.gun->copy();
	}
	return *this;
}
Ship &Ship::operator=(Ship &&ship) noexcept {
	if (this != &ship)
	{
		delete gun;
		gun = ship.gun;
		ship.gun = nullptr;
	}
	return *this;
}
Ship::Ship(const Ship &ship)
	: RigitBody2d(*texture), gun(ship.gun->copy())
{

}
Ship::Ship(Ship &&ship) noexcept
	: RigitBody2d(*texture)
{
	gun = ship.gun;
	ship.gun = nullptr;
}
