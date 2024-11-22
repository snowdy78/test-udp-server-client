#pragma once

#include "decl.hpp"

class Hittable
{
protected:
	float health	 = 100.f;
	float max_health = 100.f;
	friend class HealthBar;
	class HealthBar : public sf::Drawable, public sf::Transformable
	{
		inline static rn::StaticTexture texture = rn::StaticTexture("img/health_bar.png");
		rn::Rect ui;
		rn::Vec2f bar_size = { 30, 6 };
		rn::Rect fill_bar;
		rn::Rect back_bar;
		const Hittable &hittable;

	public:
		HealthBar(const Hittable &hittable) :
			ui({ 32, 8 }),
			hittable(hittable)
		{
			ui.setTexture(&*texture);
			fill_bar.setSize({ hittable.health * bar_size.x / 100.f, bar_size.y });
			fill_bar.setSize({ hittable.health * bar_size.x / 100.f, bar_size.y });
			fill_bar.setPosition(1, 1);
			back_bar.setPosition(1, 1);
			fill_bar.setFillColor(sf::Color::Green);
			back_bar.setFillColor(sf::Color::Red);
		}
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override
		{
			states.transform *= getTransform();
			target.draw(back_bar, states);
			target.draw(fill_bar, states);
			target.draw(ui, states);
		}
	};
    HealthBar health_bar{*this};
public:
};
