#pragma once

#include "AbstractShip.hpp"
#include "Collidable.hpp"
#include "Collider.hpp"
#include "decl.hpp"


class EnemyShip : public Collidable<PolygonCollider>, public AbstractShip
{
	inline static rn::StaticTexture texture = rn::StaticTexture("img/enemy_ship.png");
	std::unique_ptr<Gun> gun				= nullptr;

protected:
	virtual void updateCollider() override;

public:
	EnemyShip();
	~EnemyShip() override = default;
	void onMove() override;
	const Collider *getCollider() const override;
	bool resolve(const Collidable *collidable) const override;
};
