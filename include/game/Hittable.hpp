#pragma once

#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "decl.hpp"

class Hittable
{
	float health	 = 100.f;
	float max_health = 100.f;
	class HealthBar
	{
        inline static rn::StaticTexture texture = rn::StaticTexture("img/health_bar.png");
        rn::Rect ui;
        rn::Rect fill_bar;
        rn::Rect back_bar;
    public:
        HealthBar() {}
	};

public:
};
