#pragma once


#include "BulletMother.hpp"
#include "decl.hpp"


class Gun : public BulletMother, public sf::Drawable
{
protected:
	const Ship *ship;
public:
	Gun(const Ship *ship);
	virtual ~Gun() = 0;
    virtual void shoot(const rn::Vec2f &direction) = 0;
    virtual Bullet *createBullet() const = 0;
	virtual Gun *copy() const = 0;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
