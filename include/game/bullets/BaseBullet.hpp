#pragma once

#include "game/Bullet.hpp"
#include "decl.hpp"

class BaseBullet : public Bullet
{
    inline static constexpr float initial_damage = 25.f;
public:
    BaseBullet(const Gun *);
	Bullet *copy() const override;
};
