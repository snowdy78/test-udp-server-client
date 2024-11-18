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
void Collidable::update()
{
	for (auto &collidable: collidables)
	{
		if (!collidable)
			std::cerr << "collidable is null\n";
		if (getCollisionType() != CollisionType::Any)
		{
			if (getCollisionType() == CollisionType::None)
			{
				continue;
			}
			if (getCollisionType() == CollisionType::Same && castToChild(collidable))
			{
				continue;
			}
			if (getCollisionType() == CollisionType::Different && !castToChild(collidable))
			{
				continue;
			}
		}
		
		if (auto el = dynamic_cast<const EllipseCollider *>(this->getCollider()))
		{
			collidable->getCollider()->collide(*el);
		}
		else if (auto pl = dynamic_cast<const PolygonCollider *>(this->getCollider()))
		{
			collidable->getCollider()->collide(*pl);
		}
	}
}
