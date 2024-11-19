#pragma once

#include "decl.hpp"
#include "game/Gun.hpp"
#include "RigitBody2d.hpp"

class AbstractShip : public RigitBody2d
{
protected:
	std::unique_ptr<Gun> gun = nullptr;
	sf::Sprite sprite;

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
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	void start() override;
	void update() override;
	void onEvent(sf::Event &event) override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void onUpdatePosition() override;
};
