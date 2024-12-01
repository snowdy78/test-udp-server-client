#pragma once

#include "Collidable.hpp"
#include "Helpers.hpp"
#include "Hittable.hpp"
#include "RigitBody2d.hpp"
#include "SoundDisperseEntity.hpp"
#include "SpaceFieldObject.hpp"
#include "decl.hpp"
#include "game/Gun.hpp"
#include "game/colliders/EllipseCollider.hpp"


template<class T>
concept GunConcept = std::is_base_of<Gun, T>::value && !std::is_same_v<Gun, T>;

class AbstractShip : public RigitBody2d, public Collidable, public Hittable, public SpaceFieldObject
{
	friend class SpaceField;
	friend class Gun;

protected:
	std::unique_ptr<Gun> gun;
	sf::Sprite sprite;
	void updateGunPosition();
	void updateCollider();
	EllipseCollider collider;
	bool is_dead	 = false;
	bool accelerated = getVelocity() + 0.3f;

	inline static sf::SoundBuffer hit_buffer = loadSound("hit.ogg");
	SoundDisperseEntity hit_sound{ 20.f, 100.f };

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
	bool isDead() const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	const sf::Sprite &getSprite() const;
	const Collider *getCollider() const override;
	virtual void beforeDie() {}
	template<GunConcept T>
	void setGun();
	void onRotation() override;
	void onMove() override;
	void onHit() override;
	void onCollisionEnter(Collidable *collidable) override;
	bool resolve(const Collidable *collidable) const override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual AbstractShip *copy() const = 0;
};

template<GunConcept T>
void AbstractShip::setGun()
{
	gun.reset(new T(this));
}
