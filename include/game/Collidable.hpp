#pragma once

#include "Collider.hpp"
#include "decl.hpp"


class Collidable : public virtual rn::LogicalObject
{
protected:
	inline static std::vector<Collidable *> collidables{};
public:
	enum CollisionType {
		Any, Same, Different, None,
	};
	Collidable();
	virtual ~Collidable()						= 0;
	virtual const Collider *getCollider() const = 0;
	void update() override;
	void setCollisionType(CollisionType collision_type);
	CollisionType getCollisionType() const;
	virtual bool castToChild(const Collidable *collidable) const = 0;
private:
	CollisionType collision_type = Any;
};
