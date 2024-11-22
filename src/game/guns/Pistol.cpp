#include "game/guns/Pistol.hpp"
#include "game/bullets/BaseBullet.hpp"

Pistol::Pistol(const Ship *ship) :
	Gun(ship, &sound_buffer)
{}
void Pistol::shoot(const rn::Vec2f &direction)
{
	if (ship)
	{
		float angle = rn::math::rot(direction) + rn::random::real(-1.f, 1.f) * disperse_angle / 2.f;
		rn::Vec2f dir{ std::cos(angle * rn::math::rad), std::sin(angle * rn::math::rad) };
		summon(createBullet(), dir);
		sound.play();
	}
}
Bullet *Pistol::createBullet() const
{
	auto bullet = new BaseBullet;
	bullet->setPosition(getPosition());
	return bullet;
}
Gun *Pistol::copy() const
{
	return new Pistol(ship);
}
