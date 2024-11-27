#pragma once

#include "AbstractShip.hpp"
#include "decl.hpp"


class EnemyShip : public AbstractShip
{
	inline static rn::StaticTexture texture = rn::StaticTexture("img/enemy_ship.png");

public:
	EnemyShip();
	~EnemyShip() override = default;
	void movement() override;
	void rotation() override;
	void onMove() override;
	void onHit() override;
	AbstractShip *copy() const override;
};
