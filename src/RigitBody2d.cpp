#include "RigitBody2d.hpp"

rn::Vec2f RigitBody2d::countDirection() const
{
	return rn::math::norm(rn::Vec2f(rn::mouse_position) - getPosition());
}


void RigitBody2d::rotation()
{
	using namespace rn::math;
	rn::Vec2f dir_2d{getDirection().x, getDirection().y};
	const auto angle = rot(dir_2d);
	setRotation(angle);
}

void RigitBody2d::movement()
{
	using namespace rn::math;
	Direction *d_move = nullptr;
	if (rn::isKeyhold(sf::Keyboard::W))
	{
		d_move = new Direction(getDirection2d());
	}
	if (rn::isKeyhold(sf::Keyboard::S))
	{
		if (!d_move)
		{
			d_move = new Direction(-getDirection2d());
		}
		*d_move -= getDirection2d();
	}
	if (rn::isKeyhold(sf::Keyboard::A))
	{
		if (!d_move)
		{
			d_move = new Direction(nor(getDirection2d()));
		}
		*d_move += nor(getDirection2d());
	}
	if (rn::isKeyhold(sf::Keyboard::D))
	{
		if (!d_move)
		{
			d_move = new Direction(-nor(getDirection2d()));
		}
		*d_move -= nor(getDirection2d());
	}
	if (d_move)
	{
		move(velocity * d_move->x, velocity * d_move->y);
	}
	delete d_move;
}

RigitBody2d::RigitBody2d(const rn::Vec2f &size)
	:
	rect(size) {}

void RigitBody2d::setPosition(const rn::Vec2f &p)
{
	Transformable::setPosition(p);
	Listener::setPosition(p.x, p.y, 0);
	rn::Vec2f perp = rn::math::nor(getPosition());
	Listener::setUpVector(perp.x, perp.y, 0.f);
}

void RigitBody2d::setPosition(float x, float y)
{
	Transformable::setPosition(x, y);
	Listener::setPosition(x, y, 0);
	rn::Vec2f perp = rn::math::nor(getPosition());
	Listener::setUpVector(perp.x, perp.y, 0.f);
}

rn::Vec2f RigitBody2d::getPosition() const
{
	return Transformable::getPosition();
}

void RigitBody2d::move(float x, float y)
{
	Transformable::move(x, y);
	Listener::setPosition(getPosition().x + x, getPosition().y + y, 0);
	rn::Vec2f perp = rn::math::nor(getPosition());
	Listener::setUpVector(perp.x, perp.y, 0.f);
}

void RigitBody2d::move(const rn::Vec2f &p)
{
	Transformable::move(p);
	Listener::setPosition(getPosition().x + p.x, getPosition().y + p.y, 0);
	rn::Vec2f perp = rn::math::nor(getPosition());
	Listener::setUpVector(perp.x, perp.y, 0.f);
}

rn::Vec2f RigitBody2d::getDirection2d()
{
	return {getDirection().x, getDirection().y};
}

const sf::Shape &RigitBody2d::getShape() const
{
	return rect;
}

void RigitBody2d::start()
{
	setOrigin(rect.getSize() / 2.f);
}

void RigitBody2d::update()
{
	Direction dir{countDirection()};
	setDirection({dir.x, dir.y, 0});
	movement();
	rotation();
}

void RigitBody2d::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(rect, states);
}
