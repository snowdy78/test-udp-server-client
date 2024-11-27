#pragma once

#include "decl.hpp"

class Direction : public rn::Vec2f
{
public:
	explicit Direction(const rn::Vec2f &distance = {})
		: rn::Vec2f(rn::math::norm(distance))
	{}
	explicit Direction(float angle)
		: rn::Vec2f{ std::cos(angle), std::sin(angle) }
	{}
	const rn::Vec2f &toVector() const
	{
		return *this;
	}
	Direction &operator=(const rn::Vec2f &distance)
	{
		if (&distance != this)
		{
			rn::Vec2f &&direction = rn::math::norm(distance);
			x					  = direction.x;
			y					  = direction.y;
		}
		return *this;
	}
};
class RigitBody2d : public rn::MonoBehaviour
{
	float velocity = 0.3f;
	Direction direction{};
	bool is_capable = true;
public:
	using Transformable::getPosition;

	virtual void rotation() {}
	virtual void movement() {}

	explicit RigitBody2d();

	bool isCapable() const;
	void setCapability(bool capability);
	void setPosition(const rn::Vec2f &p);
	void setPosition(float x, float y);
	void setDirection(float x, float y);
	void setDirection(const rn::Vec2f &p);
	void setVelocity(float velocity);
	Direction getDirection() const;
	void move(float x, float y);
	void move(const rn::Vec2f &p);
	void setRotation(float angle);
	void rotate(float angle);

	virtual void onMove() {}
	virtual void onRotation() {}
	float getVelocity() const;
	static rn::Vec2f getDirection2d();

	const sf::Sprite &getSprite() const;

	void start() override;
	void update() override;
	void onEvent(sf::Event &event) override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
