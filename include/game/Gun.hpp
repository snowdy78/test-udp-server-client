#pragma once


#include "SoundDisperseEntity.hpp"
#include "decl.hpp"


class Gun : public sf::Transformable, public rn::LogicalObject 
{
	rn::Stopwatch clock;
	bool has_rollback = false;

protected:
	const AbstractShip *ship;
	SoundDisperseEntity sound{ 20.f, 100.f };

	void setClearSoundDistance(float distance);
	void setDisperseRadius(float radius);

	friend class Bullet;
	void startRollback();

public:
	const AbstractShip *const &user = ship;
	Gun(const AbstractShip *user, const sf::SoundBuffer *buffer = nullptr);
	virtual ~Gun() = 0;
	virtual void shoot(const rn::Vec2f &direction);
	virtual Bullet *createBullet() const	= 0;
	virtual Gun *copy() const				= 0;
	virtual rn::Vec2f getTrajectory() const = 0;
	bool hasRollback() const;
	void update() override;
	virtual float getMillisDelay() const;
};
