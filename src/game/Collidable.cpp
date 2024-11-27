#include "game/Collidable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "game/colliders/EllipseCollider.hpp"
#include "game/colliders/PolygonCollider.hpp"

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
	for (auto &collidable : collidables)
	{
		for (auto &collision : collidable->collisions_at_state)
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
void Collidable::collideObjects(Collidable *collidable, Collidable *obstacle)
{

	auto p1 = dynamic_cast<sf::Transformable *>(obstacle)->getPosition();
	auto p2 = dynamic_cast<sf::Transformable *>(collidable)->getPosition();
	if (rn::math::length(p1 - p2) > min_dist_collision)
		return;
	auto el = dynamic_cast<const EllipseCollider *>(obstacle->getCollider());
	auto pl = dynamic_cast<const PolygonCollider *>(obstacle->getCollider());
	if (obstacle == collidable || !collidable->resolve(obstacle) || !el && !pl)
		return;
	bool collision_state = false;
	if (el)
		collision_state = collidable->getCollider()->collide(*el);
	else
		collision_state = collidable->getCollider()->collide(*pl);
	collidable->setCollisionState(collision_state);
	if (collision_state || collidable->is_collided_before)
		collidable->collisions_at_state.push_back(obstacle);
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
