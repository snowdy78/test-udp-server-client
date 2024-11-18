#include "guns/Pistol.hpp"
#include "bullets/BaseBullet.hpp"

Pistol::Pistol(const Ship *ship) : Gun(ship) {}
void Pistol::shoot(const rn::Vec2f &direction)
{
	if (ship)
	{
		summon(createBullet(), direction);
	}
}
Bullet *Pistol::createBullet() const
{
	return new BaseBullet();
}
Gun *Pistol::copy() const
{
	return new Pistol(ship);
}
