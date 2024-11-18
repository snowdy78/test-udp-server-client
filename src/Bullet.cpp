#include "Bullet.hpp"

/**
 * \brief Default constructor for Bullet
 *
 * Construct a Bullet object with the image set to the contents of Bullet::texture
 */
Bullet::Bullet() : sprite(*texture)
{
	sound_buffer.loadFromFile("shoot.ogg");
	sound.setBuffer(sound_buffer);
	setOrigin(rn::Vec2f{ texture->getSize() / 2u });
	updateCollider();
}
void Bullet::update()
{
	sound.update();
	velocity += acceleration;
	move(direction * velocity);
	for (auto &collidable: collidables)
	{
		collidable->getCollider()->collide(collider);
	}
}
void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}
rn::Vec2f Bullet::getSize() const
{
	return rn::Vec2f{ sprite.getTexture()->getSize() };
}
void Bullet::setDirection(const rn::Vec2f &direction)
{
	this->direction = direction;
}
void Bullet::setMass(float mass)
{
	this->mass = mass;
}
void Bullet::setVelocity(float velocity)
{
	this->velocity = velocity;
}
void Bullet::setAcceleration(float acceleration)
{
	this->acceleration = acceleration;
}
const rn::Vec2f &Bullet::getDirection() const
{
	return direction;
}
float Bullet::getMass() const
{
	return mass;
}
float Bullet::getVelocity() const
{
	return velocity;
}
float Bullet::getAcceleration() const
{
	return acceleration;
}
bool Bullet::isIntersected(const rn::Vec2f &point) const
{
	using namespace rn::math;
	rn::math::ellipce ellipce{ rn::Circle(getSize().x / 2.f) };
	ellipce.center	 = getPosition();
	ellipce.rotation = getRotation();
	ellipce.origin	 = getOrigin();

	return ellipce.contains(point);
}
void Bullet::setPosition(float x, float y)
{
	sf::Transformable::setPosition(x, y);
	updateCollider();
}
void Bullet::setPosition(const rn::Vec2f &vector)
{
	sf::Transformable::setPosition(vector);
	updateCollider();
}
void Bullet::updateCollider()
{
	collider.transform(rn::math::ellipce(rn::Circle(getSize().x / 2.f)));
}
const Collider *Bullet::getCollider() const
{
	return &collider;
}
