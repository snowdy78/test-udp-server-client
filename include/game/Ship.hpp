#pragma once

#include "AbstractShip.hpp"
#include "decl.hpp"



class Ship : public AbstractShip
{
	inline static rn::StaticTexture texture = rn::StaticTexture("img/ship.png");

public:
	/**
	 * \brief Constructor for Ship
	 *
	 * Construct a Ship object with the image set to the contents of Ship::texture
	 */
	Ship();
	~Ship() override = default;

	void rotation() override;
	void movement() override;
	void onMove() override;
	void onRotation() override;
	void onHit() override;
	AbstractShip *copy() const override;
};
