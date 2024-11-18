#pragma once

#include "Collider.hpp"
#include "decl.hpp"


class Collidable
{
protected:
	inline static std::vector<Collidable *> collidables{};

public:
	Collidable();
	virtual ~Collidable()						= 0;
	virtual const Collider *getCollider() const = 0;
};
