#pragma once

#include "components/FileLoader.hpp"
#include "game/Gun.hpp"


class Pistol : public Gun
{
	inline static loading<sf::SoundBuffer> sound_buffer = FileLoader::Instance().addSoundToUpload("shoot.ogg").get();

	float disperse_angle = 5.f;

public:
	Pistol(const AbstractShip *ship);
	Bullet *createBullet() const override;
	rn::Vec2f getTrajectory() const override;
	Gun *copy() const override;
};
