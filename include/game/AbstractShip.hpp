#pragma once

#include "Collidable.hpp"
#include "Hittable.hpp"
#include "RigitBody2d.hpp"
#include "decl.hpp"
#include "game/Gun.hpp"
#include "game/colliders/EllipseCollider.hpp"
#include "Helpers.hpp"

class AbstractShip : public RigitBody2d, public Collidable, public Hittable
{
	friend class SpaceField;
protected:
	std::unique_ptr<Gun> gun = nullptr;
	sf::Sprite sprite;
	void updateGunPosition();
	void updateCollider();
	EllipseCollider collider;
	SpaceField *field = nullptr;
	bool is_dead	  = false;
	void setField(SpaceField *field);
	bool accelerated = getVelocity() + 0.3f;

	inline static sf::SoundBuffer hit_buffer = loadSound("hit.ogg");
	SoundDisperseEntity sound{ 20.f, 100.f };

public:
	AbstractShip(const sf::Texture &texture);
	void setGun(const Gun &gun);
	const Gun *getGun() const;
	rn::Vec2f getSize() const;
	/**
	 * \brief Shoot a bullet in the ship direction.
	 *
	 * A Gun will create a Bullet and shot in the ship direction. The direction
	 * is determined by the ship's rotation.
	 */
	void shoot();
	void start() override;
	void update() override;
	void onEvent(sf::Event &event) override;
	void onMove() override;
	bool isDead() const;
	void onRotation() override;
	void onCollisionEnter(Collidable *collidable) override;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	const sf::Sprite &getSprite() const;
	const Collider *getCollider() const override;
	void onHit() override;
	bool resolve(const Collidable *collidable) const override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual AbstractShip *copy() const = 0;
};
