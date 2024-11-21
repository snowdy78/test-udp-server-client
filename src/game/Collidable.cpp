#include "game/Collidable.hpp"
#include "game/Bullet.hpp"
void Collidable::setCollisionExist(bool value)
{
	if (is_collide != value) 
	{
		is_collided_before = is_collide;
		is_collide = value;
	}
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
	is_collide = false;

	std::cout << "start\n";
	for (auto &collidable: collidables)
	{
		std::cout << "is bullet: " << bool(dynamic_cast<const Bullet *>(collidable)) << "\n";
		std::cout << "collidable: " << collidable << "\n";
		std::cout << "collidable2: " << this << "\n";
		std::cout << "resolve: " << resolve(collidable) << "\n";
		std::cout << "resolve2: " << collidable->resolve(this) << "\n";
		if (!collidable || this == collidable || !resolve(collidable))
		{
			continue;
		}

		if (auto el = dynamic_cast<const EllipseCollider *>(getCollider()))
		{
			bool collision_state = collidable->getCollider()->collide(*el);
			setCollisionExist(collision_state);
			std::cout << "asdfsa\n";
			if (collision_state)
				collisions.push_back(collidable);
		}
		else if (auto pl = dynamic_cast<const PolygonCollider *>(getCollider()))
		{
			bool collision_state = collidable->getCollider()->collide(*el);
			setCollisionExist(collision_state);
			if (collision_state)
				collisions.push_back(collidable);
		}
	}
	std::cout << "end\n";
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
