#pragma once

#include "Collidable.hpp"
#include "Collider.hpp"
#include "decl.hpp"
#include "AbstractShip.hpp"


class Ship : public Collidable<PolygonCollider>, public AbstractShip
{
	inline static rn::StaticTexture texture = rn::StaticTexture("img/ship.png");
	std::unique_ptr<Gun> gun								= nullptr;

protected:
	virtual void updateCollider() override;

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
	void onUpdatePosition() override;
	
	const Collider *getCollider() const override;
	bool resolve(const Collidable *collidable) const override;
};
