#pragma once

#include "decl.hpp"

class Direction : public rn::Vec2f
{
public:
	explicit Direction(const rn::Vec2f &distance) : rn::Vec2f(rn::math::norm(distance)) {}
	explicit Direction(float angle) : rn::Vec2f{std::cos(angle), std::sin(angle)} {}
	const rn::Vec2f &toVector() const
	{
		return *this;
	}
	Direction &operator=(const rn::Vec2f &distance)
	{
		if (&distance != this)
		{
			rn::Vec2f &&direction = rn::math::norm(distance);
			x = direction.x;
			y = direction.y;
		}
		return *this;
	}
};

class RigitBody2d : public rn::MonoBehaviour, public sf::Listener
{
	rn::Rect rect;
	float velocity = 0.1f;
	rn::Vec2f countDirection() const;
	void rotation();

	void movement();

public:
	using Transformable::getPosition;
	explicit RigitBody2d(const rn::Vec2f &size);

	void setPosition(const rn::Vec2f &p);

	void setPosition(float x, float y);

	rn::Vec2f getPosition() const;
	void move(float x, float y);
	void move(const rn::Vec2f &p);
	static rn::Vec2f getDirection2d();

	const sf::Shape &getShape() const;

	void start() override;

	void update() override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
