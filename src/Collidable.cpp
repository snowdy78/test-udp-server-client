#include "Collidable.hpp"

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
