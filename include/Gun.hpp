#pragma once


#include "BulletMother.hpp"
#include "decl.hpp"


class Gun : public BulletMother
{
	const Ship *ship;

public:
	Gun(Ship *ship);
	virtual ~Gun() = 0;
    virtual void shoot(const rn::Vec2f &direction) = 0;
    virtual Bullet *createBullet() const = 0;
};
