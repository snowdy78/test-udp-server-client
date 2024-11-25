#include "game/Collidable.hpp"

void Collidable::setCollisionState(bool value)
{
	is_collide = is_collide || value;
}
bool Collidable::isCollisionEnter() const
{
	return is_collide && !is_collided_before;
}

bool Collidable::isCollisionUpdate() const
{
	return is_collide && is_collided_before;
}

bool Collidable::isCollisionEnd() const
{
	return !is_collide && is_collided_before;
}

Collidable::~Collidable()
{
	auto i = std::find(collidables.begin(), collidables.end(), this);
	if (i != collidables.end())
		collidables.erase(i);
}

Collidable::Collidable()
{
	collidables.push_back(this);
}

void Collidable::updateCollisionState()
{
	std::vector<Collidable *> collisions{};
	resetCollisionState();

	for (auto &collidable: collidables)
	{
		if (!collidable || this == collidable || !resolve(collidable))
		{
			continue;
		}
		if (auto el = dynamic_cast<const EllipseCollider *>(getCollider()))
		{
			bool collision_state = collidable->getCollider()->collide(*el);
			setCollisionState(collision_state);
			if (collision_state || is_collided_before)
				collisions.push_back(collidable);
		}
		else if (auto pl = dynamic_cast<const PolygonCollider *>(getCollider()))
		{
			bool collision_state = collidable->getCollider()->collide(*pl);
			setCollisionState(collision_state);
			if (collision_state || is_collided_before)
				collisions.push_back(collidable);
		}
	}
	for (auto &collision: collisions)
	{
		if (isCollisionEnter())
			onCollisionEnter(collision);
		else if (isCollisionUpdate())
			onCollisionUpdate(collision);
		else if (isCollisionEnd())
			onCollisionEnd(collision);
	}
}
void Collidable::resetCollisionState()
{
	is_collided_before = is_collide;
	is_collide = false;
}
