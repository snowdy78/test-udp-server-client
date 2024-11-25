#pragma once

#include "Collider.hpp"
#include "decl.hpp"

class Collidable
{
	inline static std::vector<Collidable *> collidables{};
	bool is_collide			= false;
	bool is_collided_before = false;
	std::vector<Collidable *> collisions_at_state{};
	void setCollisionState(bool value);
	static bool collideObjects(Collidable *collidable, Collidable *obstacle);
	void resetCollisionState();

public:
	Collidable();
	virtual ~Collidable()						= 0;
	virtual const Collider *getCollider() const = 0;
	static void updateCollisionState();
	virtual void onCollisionEnter(Collidable *collidable) {}
	virtual void onCollisionUpdate(Collidable *collidable) {}
	virtual void onCollisionEnd(Collidable *collidable) {}
	bool isCollisionEnter() const;
	bool isCollisionUpdate() const;
	bool isCollisionEnd() const;
	virtual bool resolve(const Collidable *collidable) const = 0;
};
