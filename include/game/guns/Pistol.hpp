#pragma once

#include "game/Gun.hpp"

class Pistol : public Gun
{
	float disperse_angle = 5.f;
public:
    Pistol(const Ship *ship);
	void shoot(const rn::Vec2f &direction) override;
	Bullet *createBullet() const override;
	Gun *copy() const override;
};
