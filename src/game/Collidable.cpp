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
	for (auto &collidable: collidables)
	{
		collidable->collisions_at_state.clear();
		collidable->resetCollisionState();
		for (auto &obstacle: collidables)
		{
			collideObjects(collidable, obstacle);
		}
	}
	for (auto &collidable: collidables)
	{
		for (auto &collision: collidable->collisions_at_state)
		{
			if (collidable->isCollisionEnter())
				collidable->onCollisionEnter(collision);
			else if (collidable->isCollisionUpdate())
				collidable->onCollisionUpdate(collision);
			else if (collidable->isCollisionEnd())
				collidable->onCollisionEnd(collision);
		}
	}
}
void Collidable::resetCollisionState()
{
	is_collided_before = is_collide;
	is_collide		   = false;
}
bool Collidable::collideObjects(Collidable *collidable, Collidable *obstacle)
{
	if (obstacle == collidable || !obstacle->resolve(collidable))
	{
		return false;
	}
	if (auto el = dynamic_cast<const EllipseCollider *>(obstacle->getCollider()))
	{
		bool collision_state = collidable->getCollider()->collide(*el);
		obstacle->setCollisionState(collision_state);
		if (collision_state || obstacle->is_collided_before)
			obstacle->collisions_at_state.push_back(collidable);
		return true;
	}
	else if (auto pl = dynamic_cast<const PolygonCollider *>(obstacle->getCollider()))
	{
		bool collision_state = collidable->getCollider()->collide(*pl);
		obstacle->setCollisionState(collision_state);
		if (collision_state || obstacle->is_collided_before)
			obstacle->collisions_at_state.push_back(collidable);
		return true;
	}
	return false;
}
