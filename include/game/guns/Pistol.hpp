#pragma once

#include "components/FileLoader.hpp"
#include "game/Gun.hpp"


class Pistol : public Gun
{
	inline static const sf::SoundBuffer *const &sound_buffer = FileLoader::Instance().addSoundToUpload("shoot.ogg");

	float disperse_angle = 5.f;

public:
	Pistol(const AbstractShip *ship);
	Bullet *createBullet() const override;
	rn::Vec2f getTrajectory() const override;
	Gun *copy() const override;
};
