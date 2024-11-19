#include "game/Ship.hpp"
#include "game/AbstractShip.hpp"
#include "game/Gun.hpp"

Ship::Ship() : AbstractShip(*texture) {}

void Ship::rotation()
{
	using namespace rn::math;
	rn::Vec2f dir_2d{ getDirection().x, getDirection().y };
	const auto angle = rot(dir_2d);
	setRotation(angle);
}

void Ship::movement()
{
	using namespace rn::math;
	std::unique_ptr<Direction> d_move = nullptr;
	if (rn::isKeyhold(sf::Keyboard::W))
	{
		d_move = std::make_unique<Direction>(getDirection2d());
	}
	if (rn::isKeyhold(sf::Keyboard::S))
	{
		if (!d_move)
		{
			d_move = std::make_unique<Direction>(-getDirection2d());
		}
		*d_move -= getDirection2d();
	}
	if (rn::isKeyhold(sf::Keyboard::A))
	{
		if (!d_move)
		{
			d_move = std::make_unique<Direction>(nor(getDirection2d()));
		}
		*d_move += nor(getDirection2d());
	}
	if (rn::isKeyhold(sf::Keyboard::D))
	{
		if (!d_move)
		{
			d_move = std::make_unique<Direction>(-nor(getDirection2d()));
		}
		*d_move -= nor(getDirection2d());
	}
	if (d_move)
	{
		move(getVelocity() * d_move->x, getVelocity() * d_move->y);
	}
}
bool Ship::resolve(const Collidable *collidable) const
{
	return dynamic_cast<const Bullet *>(collidable);
}

const Collider *Ship::getCollider() const
{
	return &collider;
}
void Ship::updateCollider()
{
	rn::math::rectangle rect{ getGlobalBounds() };
	collider.transform(rect);
}
void Ship::onUpdatePosition()
{
	AbstractShip::onUpdatePosition();
	updateCollider();
}
