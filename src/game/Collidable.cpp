#include "game/Collidable.hpp"
#include <stdexcept>
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
	: before(false),
	  current(is_collide)
{}

Collidable::CollisionState Collidable::getCollisionState(Collidable *obstacle) const
{
	const collision_traits *state;
	try
	{
		state = &collision_states.at(obstacle);
	}
	catch (std::out_of_range &exception)
	{
		return None;
	}

	if (state->current && !state->before)
		return Enter;

	if (state->current && state->before)
		return Update;

	if (!state->current && state->before)
		return End;

	return None;
}

Collidable::~Collidable()
{
	auto i = std::find(collidables.begin(), collidables.end(), this);
	if (i != collidables.end())
	{
		collidables.erase(i);
		for (auto &collidable: collidables)
		{
			try
			{
				collidable->collision_states.erase(this);
			}
			catch (std::out_of_range &err)
			{}
		}
	}
}

Collidable::Collidable()
{
	collidables.push_back(this);
}

void Collidable::updateCollisionState()
{
	for (size_t i = 0; i < collidables.size() - 1; i++)
	{
		auto &collidable = collidables[i];
		for (size_t j = i + 1; j < collidables.size(); j++)
		{
			auto &obstacle = collidables[j];
			collideObjects(collidable, obstacle);
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
	auto p1 = dynamic_cast<sf::Transformable *>(obstacle)->getPosition();
	auto p2 = dynamic_cast<sf::Transformable *>(collidable)->getPosition();
	if (rn::math::length(p1 - p2) > min_dist_collision)
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
	collision_traits *state;
	try
	{
		state = &collision_states.at(obstacle);
	}
	catch (std::out_of_range &exception)
	{
		// append collision enter state
		collision_states.insert({ obstacle, value });
		return;
	}
	// update state
	state->set(value);

	// if no collision remove state
	if (!state->current && !state->before)
	{
		collision_states.erase(obstacle);
	}
}
