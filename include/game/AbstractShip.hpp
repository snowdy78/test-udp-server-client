#pragma once

#include "RigitBody2d.hpp"
#include "Collidable.hpp"
#include "decl.hpp"
#include "game/Gun.hpp"


class AbstractShip : public RigitBody2d, public Collidable
{
protected:
	std::unique_ptr<Gun> gun = nullptr;
	sf::Sprite sprite;
	void updateGunPosition();
	void updateCollider();
	PolygonCollider collider;
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
	void onRotation() override;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	const sf::Sprite &getSprite() const;
	const Collider *getCollider() const override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
