#pragma once

#include "RigitBody2d.hpp"
#include "decl.hpp"


class Ship : public RigitBody2d
{
	inline static rn::StaticTexture texture = rn::StaticTexture("img/ship.png");

public:
	Ship();

	void shoot(rn::Vec2f direction)
	{}
};
