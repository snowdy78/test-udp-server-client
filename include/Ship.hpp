#pragma once

#include "decl.hpp"
#include "RigitBody2d.hpp"

class Ship : public RigitBody2d
{
	inline static rn::StaticTexture texture = rn::StaticTexture("img/ship.png");

public:
    Ship();
    
    void shoot(rn::Vec2f direction) 
    {
        
    }
};
