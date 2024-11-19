#include "game/AbstractShip.hpp"
#include "game/RigitBody2d.hpp"

AbstractShip::AbstractShip(const sf::Texture &texture) : sprite(texture) {}
rn::Vec2f AbstractShip::getSize() const
{
	return rn::Vec2f(sprite.getTexture()->getSize());
}
const Gun *AbstractShip::getGun() const
{
	return gun.get();
}
void AbstractShip::setGun(const Gun &gun)
{
	this->gun.reset(gun.copy());
	updateGunPosition();
}
void AbstractShip::shoot()
{
	if (!gun)
	{
		return;
	}
	gun->shoot(getDirection());
}
sf::FloatRect AbstractShip::getLocalBounds() const
{
	return { {}, getSize() };
}
sf::FloatRect AbstractShip::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

void AbstractShip::start()
{
	RigitBody2d::start();
	setOrigin(getSize() / 2.f);
	if (gun)
		gun->start();
	onMove();
}

void AbstractShip::update()
{
	RigitBody2d::update();
	if (gun)
		gun->update();
}

void AbstractShip::onEvent(sf::Event &event)
{
	RigitBody2d::onEvent(event);
	if (gun)
	{
		gun->onEvent(event);
	}
	if (rn::isKeydown(sf::Mouse::Left))
	{
		shoot();
	}
}

void AbstractShip::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (gun)
		target.draw(*gun, states);
	target.draw(sprite, states);
}
void AbstractShip::onMove()
{
	updateGunPosition();
}
void AbstractShip::onRotation() {}
const sf::Sprite &AbstractShip::getSprite() const
{
	return sprite;
}
void AbstractShip::updateGunPosition() {
	if (gun)
		gun->setPosition(getPosition());
}
