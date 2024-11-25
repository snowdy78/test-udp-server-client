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
			if (!collideObjects(collidable, obstacle))
				continue;
		}
	}

	for (auto &collidable: collidables)
	{
		for (auto &collision: collidable->collisions_at_state)
		{
			updateState(collidable, collision);
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
	bool collision_state = false;
	if (obstacle == collidable || !collidable->resolve(obstacle))
	{
		return collision_state;
	}
	auto el = dynamic_cast<const EllipseCollider *>(obstacle->getCollider());
	auto pl = dynamic_cast<const PolygonCollider *>(obstacle->getCollider());
	if (!el && !pl)
		return collision_state;

	if (el)
		collision_state = collidable->getCollider()->collide(*el);
	else
		collision_state = collidable->getCollider()->collide(*pl);
	collidable->setCollisionState(collision_state);
	if (collision_state || collidable->is_collided_before)
		collidable->collisions_at_state.push_back(obstacle);

	return collision_state;
}
void Collidable::updateState(Collidable *collidable, Collidable *obstacle)
{
	if (collidable->isCollisionEnter())
		collidable->onCollisionEnter(obstacle);
	else if (collidable->isCollisionUpdate())
		collidable->onCollisionUpdate(obstacle);
	else if (collidable->isCollisionEnd())
		collidable->onCollisionEnd(obstacle);
}
