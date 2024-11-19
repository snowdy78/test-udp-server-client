#pragma once

#include "Collider.hpp"
#include "decl.hpp"


class Collidable
{
protected:
	inline static std::vector<Collidable *> collidables{};
	bool is_collide = false;
	bool is_collided_before = false;
public:
	enum CollisionType {
		Any, Same, Different, None,
	};
	Collidable();
	virtual ~Collidable()						= 0;
	virtual const Collider *getCollider() const = 0;
	void updateCollisionState();
	void setCollisionType(CollisionType collision_type);
	CollisionType getCollisionType() const;
	virtual void onCollisionEnter() {}
	virtual void onCollisionUpdate() {}
	virtual void onCollisionEnd() {}
	virtual bool castToChild(const Collidable *collidable) const = 0;
private:
	CollisionType collision_type = Any;
};
