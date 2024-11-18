#pragma once


#include "BulletMother.hpp"
#include "decl.hpp"


class Gun : public BulletMother
{
protected:
	const Ship *ship;
public:
	Gun(const Ship *ship);
	virtual ~Gun() = 0;
    virtual void shoot(const rn::Vec2f &direction) = 0;
    virtual Bullet *createBullet() const = 0;
	virtual Gun *copy() const = 0;
};