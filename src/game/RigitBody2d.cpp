#include "game/RigitBody2d.hpp"

rn::Vec2f RigitBody2d::countDirection() const
{
	return rn::math::norm(rn::Vec2f(rn::mouse_position) - getPosition());
}

RigitBody2d::RigitBody2d() {}

void RigitBody2d::setPosition(const rn::Vec2f &p)
{
	sf::Transformable::setPosition(p);
	Listener::setPosition(p.x, p.y, 0);
	rn::Vec2f perp = rn::math::nor(getPosition());
	Listener::setUpVector(perp.x, perp.y, 0.f);
	onUpdatePosition();
}

void RigitBody2d::setPosition(float x, float y)
{
	Transformable::setPosition(x, y);
	Listener::setPosition(x, y, 0);
	rn::Vec2f perp = rn::math::nor(getPosition());
	Listener::setUpVector(perp.x, perp.y, 0.f);
	onUpdatePosition();
}

void RigitBody2d::move(float x, float y)
{
	Transformable::move(x, y);
	Listener::setPosition(getPosition().x + x, getPosition().y + y, 0);
	rn::Vec2f perp = rn::math::nor(getPosition());
	Listener::setUpVector(perp.x, perp.y, 0.f);
	onUpdatePosition();
}

void RigitBody2d::move(const rn::Vec2f &p)
{
	Transformable::move(p);
	Listener::setPosition(getPosition().x + p.x, getPosition().y + p.y, 0);
	rn::Vec2f perp = rn::math::nor(getPosition());
	Listener::setUpVector(perp.x, perp.y, 0.f);
	onUpdatePosition();
}

rn::Vec2f RigitBody2d::getDirection2d()
{
	return { getDirection().x, getDirection().y };
}

void RigitBody2d::update()
{
	Direction dir{ countDirection() };
	setDirection({ dir.x, dir.y, 0 });
	movement();
	rotation();
}

void RigitBody2d::onEvent(sf::Event &event) {}

void RigitBody2d::draw(sf::RenderTarget &target, sf::RenderStates states) const {}
float RigitBody2d::getVelocity() const
{
	return velocity;
}
void RigitBody2d::start() {}
