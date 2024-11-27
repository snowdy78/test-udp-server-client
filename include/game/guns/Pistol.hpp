#pragma once

#include "game/Gun.hpp"
#include "Helpers.hpp"

class Pistol : public Gun
{
	inline static sf::SoundBuffer sound_buffer = loadSound("shoot.ogg");

	float disperse_angle = 5.f;
public:
    Pistol(const AbstractShip *ship);
	void shoot(const rn::Vec2f &direction) override;
	Bullet *createBullet() const override;
	Gun *copy() const override;
};
