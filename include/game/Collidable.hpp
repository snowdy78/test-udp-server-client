#pragma once

#include "Collider.hpp"
#include "decl.hpp"

class Collidable
{
	struct collision_traits
	{
		bool before	 = false;
		bool current = false;
		friend class Collidable;

	public:
		collision_traits(bool is_collide);
		void reset();
		void set(bool is_collide);
		bool getCurrent() const;
		bool getBefore() const;
	};
	inline static std::vector<Collidable *> collidables{};
	inline static constexpr float min_dist_collision = 100.f;
	std::map<Collidable *, collision_traits> collision_states{};
	void setCollisionState(Collidable *obstacle, bool value);
	static void collideObjects(Collidable *collidable, Collidable *obstacle);
	void updateState(Collidable *obstacle);

public:

	enum CollisionState
	{
		None,
		Enter,
		Update,
		End
	};

	Collidable();
	virtual ~Collidable()						= 0;
	virtual const Collider *getCollider() const = 0;
	static void updateCollisionState();
	virtual void onCollisionEnter(Collidable *collidable) {}
	virtual void onCollisionUpdate(Collidable *collidable) {}
	virtual void onCollisionEnd(Collidable *collidable) {}
	CollisionState getCollisionState(Collidable *collidable) const;
	virtual bool resolve(const Collidable *collidable) const = 0;
};
