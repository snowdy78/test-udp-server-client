#pragma once

#include "RigitBody2d.hpp"
#include "decl.hpp"


class Ship : public RigitBody2d
{
	inline static rn::StaticTexture texture = rn::StaticTexture("img/ship.png");
    Gun *gun = nullptr;
public:

	/**
	* \brief Constructor for Ship
	*
	* Construct a Ship object with the image set to the contents of Ship::texture
	*/
	Ship();
	Ship(const Ship &ship);
	Ship(Ship &&ship) noexcept;
	~Ship();

	void setPosition(float x, float y) override;
	void setPosition(const rn::Vec2f &vector) override;
	void move(float x, float y) override;
	void move(const rn::Vec2f &p) override;
	void update() override;
	void onEvent(sf::Event &event) override;

	void setGun(const Gun &gun);
	/**
	 * \brief Shoot a bullet in the ship direction.
	 *
	 * A Gun will create a Bullet and shot in the ship direction. The direction
	 * is determined by the ship's rotation.
	 */
	void shoot();
	Ship &operator=(const Ship &ship);
	Ship &operator=(Ship &&ship) noexcept;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
