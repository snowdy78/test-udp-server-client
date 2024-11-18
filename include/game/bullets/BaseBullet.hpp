#pragma once

#include "../Bullet.hpp"

class BaseBullet : public Bullet
{
public:
    BaseBullet();
	Bullet *copy() const override;
};
