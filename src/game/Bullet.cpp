#include "game/Bullet.hpp"
#include "game/AbstractShip.hpp"
#include "game/Gun.hpp"
/**
 * \brief Default constructor for Bullet
 *
 * Construct a Bullet object with the image set to the contents of Bullet::texture
 */
Bullet::Bullet(const Gun *gun)
	: sprite(*texture),
	  author(gun)
{
	setOrigin(rn::Vec2f{ texture->getSize() / 2u });
	updateCollider();
}
Bullet::~Bullet() {}

void Bullet::update()
{
	velocity += acceleration;
	acceleration *= 0.99f;
	move(direction * velocity);
}
void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform = getTransform();
	target.draw(sprite, states);
}
rn::Vec2f Bullet::getSize() const
{
	return rn::Vec2f{ sprite.getTexture()->getSize() };
}
void Bullet::setDirection(const rn::Vec2f &direction)
{
	this->direction = rn::math::norm(direction);
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
	return collider.getColliderShape().contains(point);
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
void Bullet::move(float x, float y)
{
	sf::Transformable::move(x, y);
	updateCollider();
}
void Bullet::move(const rn::Vec2f &p)
{
	sf::Transformable::move(p);
	updateCollider();
}

void Bullet::updateCollider()
{
	rn::Circle circle(getSize().x / 2.f);
	circle.setScale(getScale());
	circle.setOrigin(getOrigin());
	circle.setPosition(getPosition());
	circle.setRotation(getRotation());
	collider.transform(circle);
}
const Collider *Bullet::getCollider() const
{
	return &collider;
}

bool Bullet::resolve(const Collidable *collidable) const
{
	return dynamic_cast<const Hittable *>(collidable)
		   && (!gun || dynamic_cast<const AbstractShip *>(collidable) != gun->user);
}
const sf::Sprite &Bullet::getSprite() const
{
	return sprite;
}
void Bullet::destroy() const
{
	if (author)
	{
		const_cast<Gun *>(author)->destroy(this);
	}
}
void Bullet::onCollisionEnter(Collidable *obstacle)
{
	if (auto hittable = dynamic_cast<Hittable *>(obstacle))
	{
		destroy();
	}
}
