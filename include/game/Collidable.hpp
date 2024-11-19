#pragma once

#include "Collider.hpp"
#include "decl.hpp"

template<ColliderType T>
class Collidable
{
protected:
	inline static std::vector<Collidable *> collidables{};
	bool is_collide = false;
	bool is_collided_before = false;
	T collider;
	virtual void updateCollider() {}

public:
	Collidable();
	virtual ~Collidable()						= 0;
	virtual const Collider *getCollider() const = 0;
	void updateCollisionState();
	virtual void onCollisionEnter(Collidable *collidable) {}
	virtual void onCollisionUpdate(Collidable *collidable) {}
	virtual void onCollisionEnd(Collidable *collidable) {}
	virtual bool resolve(const Collidable *collidable) const = 0;
};
template<ColliderType T>
Collidable<T>::~Collidable()
{
	auto i = std::find(collidables.begin(), collidables.end(), this);
	if (i != collidables.end())
		collidables.erase(i);
}
template<ColliderType T>
Collidable<T>::Collidable()
{
	collidables.push_back(this);
}
template<ColliderType T>
void Collidable<T>::updateCollisionState()
{
	std::vector<Collidable *> collisions{};

	is_collide = false;
	if (!resolve(this))
		return;

	for (auto &collidable: collidables)
	{
		if (!collidable || this == collidable || !resolve(collidable))
		{
			continue;
		}

		if (auto el = dynamic_cast<const EllipseCollider *>(getCollider()))
		{
			is_collided_before = is_collide;
			if (!is_collide)
				is_collide = collidable->getCollider()->collide(*el);
			if (collidable->getCollider()->collide(*el))
				collisions.push_back(collidable);
		}
		else if (auto pl = dynamic_cast<const PolygonCollider *>(getCollider()))
		{
			is_collided_before = is_collide;
			if (!is_collide)
				is_collide = collidable->getCollider()->collide(*pl);
			if (collidable->getCollider()->collide(*pl))
				collisions.push_back(collidable);
		}
	}
	for (auto &collision: collisions)
	{
		if (is_collide && !is_collided_before)
			onCollisionEnter(collision);
		else if (is_collide && is_collided_before)
			onCollisionUpdate(collision);
		else if (!is_collide && is_collided_before)
			onCollisionEnd(collision);
	}
}
