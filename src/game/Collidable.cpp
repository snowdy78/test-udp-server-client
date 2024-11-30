#include "game/Collidable.hpp"
#include "game/colliders/EllipseCollider.hpp"
#include "game/colliders/PolygonCollider.hpp"

void Collidable::collision_traits::reset()
{
	before	= false;
	current = false;
}
void Collidable::collision_traits::set(bool is_collide)
{
	before	= current;
	current = is_collide;

	if (current && !before)
		state = Enter;
	else if (current && before)
		state = Update;
	else if (!current && before)
		state = End;
	else
		state = None;
}

bool Collidable::collision_traits::getCurrent() const
{
	return current;
}
bool Collidable::collision_traits::getBefore() const
{
	return before;
}
Collidable::collision_traits::collision_traits(bool is_collide)
{
	set(is_collide);
}

Collidable::CollisionState Collidable::getCollisionState(Collidable *obstacle) const
{
	auto it = collision_states.find(obstacle);
	if (it == collision_states.end())
		return None;

	return it->second.state;
}

Collidable::~Collidable()
{
	auto i = std::find(collidables.begin(), collidables.end(), this);
	if (i != collidables.end())
	{
		collidables.erase(i);
		for (auto &collidable: collidables)
		{
			if (auto it = collidable->collision_states.find(this); it != collidable->collision_states.end())
				collidable->collision_states.erase(it);
		}
	}
}

Collidable::Collidable()
{
	collidables.push_back(this);
}

void Collidable::updateCollisionState()
{
	if (collidables.size() == 0)
		return;
	for (size_t i = 0; i < collidables.size() - 1; i++)
	{
		for (size_t j = i + 1; j < collidables.size(); j++)
		{
			collideObjects(collidables[i], collidables[j]);
		}
	}
	for (auto &collidable: collidables)
	{
		for (auto &state: collidable->collision_states)
		{
			collidable->updateState(state.first);
		}
	}
}
void Collidable::collideObjects(Collidable *collidable, Collidable *obstacle)
{
	auto o1 = dynamic_cast<sf::Transformable *>(obstacle);
	auto o2 = dynamic_cast<sf::Transformable *>(collidable);
	if (o1 && o2 && rn::math::length(o1->getPosition() - o2->getPosition()) > min_dist_collision)
		return;

	auto el = dynamic_cast<const EllipseCollider *>(obstacle->getCollider());
	auto pl = dynamic_cast<const PolygonCollider *>(obstacle->getCollider());
	if (obstacle == collidable || !collidable->resolve(obstacle) || !el && !pl)
		return;
	bool is_collide = false;
	if (el)
		is_collide = collidable->getCollider()->collide(*el);
	else
		is_collide = collidable->getCollider()->collide(*pl);
	auto &obstates	 = obstacle->collision_states;
	auto &collstates = collidable->collision_states;
	if (!is_collide && obstates.find(collidable) == obstates.end() && collstates.find(obstacle) == collstates.end())
		return;

	collidable->setCollisionState(obstacle, is_collide);
	if (obstacle->resolve(collidable))
		obstacle->setCollisionState(collidable, is_collide);
}
void Collidable::updateState(Collidable *obstacle)
{
	auto state = getCollisionState(obstacle);
	if (state == Enter)
		onCollisionEnter(obstacle);
	else if (state == Update)
		onCollisionUpdate(obstacle);
	else if (state == End)
		onCollisionEnd(obstacle);
}
void Collidable::setCollisionState(Collidable *obstacle, bool value)
{
	auto it = collision_states.find(obstacle);
	if (it == collision_states.end())
	{
		// append collision enter state
		collision_states.emplace(obstacle, value);
		return;
	}
	auto &traits = it->second;
	// update state
	traits.set(value);

	// if no collision remove state
	if (!traits.current && !traits.before)
	{
		collision_states.erase(obstacle);
	}
}
Collidable *Collidable::getObstacle(size_t index)
{
	auto it = collision_states.begin();
	std::advance(it, index);
	return it->first;
}
const Collidable *Collidable::getObstacle(size_t index) const
{
	auto it = collision_states.begin();
	std::advance(it, index);
	return it->first;
}
size_t Collidable::getCollisionCount() const
{
	return collision_states.size();
}
