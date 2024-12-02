#pragma once

#include "decl.hpp"
#include "DamageDealer.hpp"
#include "Collidable.hpp"
#include "colliders/EllipseCollider.hpp"
#include "SpaceFieldObject.hpp"

class Bullet : public rn::MonoBehaviour, public Collidable, virtual public DamageDealer, public SpaceFieldObject
{
	inline static rn::StaticTexture texture{ "img/bullet_shoot.png" };
	sf::Sprite sprite;

	float mass		   = 0.100f;
	float velocity	   = 15.f;
	float acceleration = (0.2f - 0.1f) / 250.f;
	rn::Vec2f direction{};
	EllipseCollider collider;
	const Gun *author = nullptr;

protected:
	void updateCollider();
	void setTexture(const sf::Texture &texture);
	const sf::Texture &getTexture() const;

public:
	Gun const *const &gun = author;
	Bullet(const Gun *gun);
	~Bullet() override = 0;
	void setDirection(const rn::Vec2f &direction);
	void setMass(float mass);
	void setVelocity(float velocity);
	void setAcceleration(float acceleration);
	void setPosition(float x, float y);
	void setPosition(const rn::Vec2f &vector);
	void move(float x, float y);
	void move(const rn::Vec2f &p);

	const rn::Vec2f &getDirection() const;
	const sf::Sprite &getSprite() const;
	float getMass() const;
	float getVelocity() const;
	float getAcceleration() const;
	rn::Vec2f getSize() const;

	void destroy() const;

	virtual void beforeDestroy() const {}
	void onCollisionEnter(Collidable *obstacle) override;

	bool isIntersected(const rn::Vec2f &point) const override;
	const Collider *getCollider() const override;
	/**
	 * \brief Resolves a collision between this Bullet and the given Collidable.
	 *
	 * The collision is resolved if the Collidable is not a Bullet.
	 *
	 * \param collidable The collidable to check against.
	 * \return True if the collision is resolved, false otherwise.
	 */
	bool resolve(const Collidable *collidable) const override;
	void update() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual Bullet *copy() const = 0;
};
