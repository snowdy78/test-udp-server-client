#include "game/Collidable.hpp"
#include "game/Collider.hpp"

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
void Collidable::setCollisionType(CollisionType collision_type)
{
	this->collision_type = collision_type;
}
Collidable::CollisionType Collidable::getCollisionType() const
{
	return collision_type;
}
void Collidable::updateCollisionState()
{
	is_collide = false;
	if (getCollisionType() == CollisionType::None)
		return;

	for (auto &collidable: collidables)
	{
		if (!collidable 
			|| this == collidable 
			|| collidable->getCollisionType() == CollisionType::None
			|| collidable->getCollisionType() == CollisionType::Same && castToChild(collidable)
			|| collidable->getCollisionType() == CollisionType::Different && !castToChild(collidable))
		{
			continue;
		}

		if (auto el = dynamic_cast<const EllipseCollider *>(getCollider()))
		{
			is_collided_before = is_collide;
			is_collide = collidable->getCollider()->collide(*el);
			return;
		}
		else if (auto pl = dynamic_cast<const PolygonCollider *>(getCollider()))
		{
			is_collided_before = is_collide;
			is_collide = collidable->getCollider()->collide(*pl);
			return;
		}
	}
}
