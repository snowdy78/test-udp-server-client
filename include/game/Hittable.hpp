#pragma once

#include "decl.hpp"

class Hittable
{
	float health	 = 100.f;
	float max_health = 100.f;

protected:
	friend class HealthBar;
	class HealthBar : public sf::Drawable, public sf::Transformable
	{
		inline static rn::StaticTexture texture = rn::StaticTexture("img/health_bar.png");
		rn::Rect ui;
		rn::Vec2f bar_size = { 30, 6 };
		rn::Rect fill_bar;
		rn::Rect back_bar;
		const Hittable &hittable;
		void updateHealthBar();
		friend class Hittable;

	public:
		HealthBar(const Hittable &hittable);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	};
	HealthBar health_bar{ *this };

public:
	float getMaxHealth() const;
	void takeDamage(float damage);
	float getHealth();
	virtual void onHit();
};
