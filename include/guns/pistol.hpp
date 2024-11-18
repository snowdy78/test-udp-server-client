#pragma once

#include "Gun.hpp"
#include "bullets/BaseBullet.hpp"

class Pistol : public Gun
{
public:
    Pistol(const Ship *ship);
	void shoot(const rn::Vec2f &direction) override;
	Bullet *createBullet() const override;
	Gun *copy() const override;
};
