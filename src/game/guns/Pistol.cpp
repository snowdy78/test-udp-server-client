#include "game/guns/Pistol.hpp"
#include "game/AbstractShip.hpp"
#include "game/bullets/BaseBullet.hpp"

Pistol::Pistol(const AbstractShip *ship)
	: Gun(ship, sound_buffer)
{}
Bullet *Pistol::createBullet() const
{
	auto bullet = new BaseBullet(this);
	bullet->setPosition(getPosition());
	return bullet;
}
Gun *Pistol::copy() const
{
	return new Pistol(user);
}
rn::Vec2f Pistol::getTrajectory() const
{
	float angle = rn::math::rot(ship->getDirection()) + rn::random::real(-1.f, 1.f) * disperse_angle / 2.f;
	return { std::cos(angle * rn::math::rad), std::sin(angle * rn::math::rad) };
}
