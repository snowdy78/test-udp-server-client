#pragma once


#include "BulletMother.hpp"
#include "SoundDisperseEntity.hpp"
#include "decl.hpp"


class Gun : public BulletMother, public sf::Drawable
{
protected:
	SoundDisperseEntity sound{ 20.f, 100.f };

	const AbstractShip *ship;

	void setClearSoundDistance(float distance)
	{
		sound.setClearSoundDistance(distance);
	}
	void setDisperseRadius(float radius)
	{
		sound.setDisperseRadius(radius);
	}
	friend class Bullet;
public:
	const AbstractShip *const &user = ship;
	Gun(const AbstractShip *user, const sf::SoundBuffer *buffer = nullptr);
	virtual ~Gun()								   = 0;
	virtual void shoot(const rn::Vec2f &direction) = 0;
	virtual Bullet *createBullet() const		   = 0;
	virtual Gun *copy() const					   = 0;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
