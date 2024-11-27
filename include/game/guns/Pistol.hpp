#pragma once

#include "game/Gun.hpp"
#include "Helpers.hpp"

class Pistol : public Gun
{
	inline static sf::SoundBuffer sound_buffer = loadSound("shoot.ogg");

	float disperse_angle = 5.f;
public:
    Pistol(const AbstractShip *ship);
	Bullet *createBullet() const override;
	rn::Vec2f getTrajectory() const override;
	Gun *copy() const override;
};
