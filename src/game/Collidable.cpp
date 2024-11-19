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
	for (auto &collidable: collidables)
	{
		collidable->is_collide = false;
	}
	for (auto &collidable1: collidables)
	{
		if (!collidable1 || collidable1->is_collide || collidable1->getCollisionType() == CollisionType::None)
		{
			continue;
		}
		for (auto &collidable2: collidables)
		{
			if (!collidable2)
			{
				std::cerr << "collidable is null\n";
				continue;
			}
			if (collidable1 == collidable2 || collidable2->is_collide
				|| collidable2->getCollisionType() == CollisionType::None
				|| collidable1->getCollisionType() == CollisionType::Same && collidable1->castToChild(collidable2)
				|| collidable1->getCollisionType() == CollisionType::Different
					   && !collidable1->castToChild(collidable2))
			{
				continue;
			}

			if (auto el = dynamic_cast<const EllipseCollider *>(collidable1->getCollider()))
			{
				collidable1->is_collided_before = collidable1->is_collide;
				collidable2->is_collided_before = collidable2->is_collide;
				collidable1->is_collide = collidable2->is_collide = collidable2->getCollider()->collide(*el);
			}
			else if (auto pl = dynamic_cast<const PolygonCollider *>(collidable1->getCollider()))
			{
				collidable1->is_collided_before = collidable1->is_collide;
				collidable2->is_collided_before = collidable2->is_collide;
				collidable1->is_collide = collidable2->is_collide = collidable2->getCollider()->collide(*pl);
			}
		}
	}
}
