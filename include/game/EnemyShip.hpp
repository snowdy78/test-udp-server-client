#pragma once

#include "AbstractShip.hpp"
#include "components/FileLoader.hpp"
#include "decl.hpp"


class EnemyShip : public AbstractShip
{
	inline static loading<sf::Texture> texture = FileLoader::Instance().addTextureToUpload("img/enemy_ship.png").get();
	inline static constexpr float min_distance_to_target = 100.f;
	sf::Clock clock;
	AbstractShip *target			   = nullptr;
	std::unique_ptr<int> randomly_move = nullptr;
	bool ready_to_shoot				   = false;

public:
	EnemyShip();
	~EnemyShip() override = default;
	void setTarget(AbstractShip *ship);
	const AbstractShip *getTarget() const;
	void update() override;
	void movement() override;
	void rotation() override;
	void onMove() override;
	void onHit() override;
	AbstractShip *copy() const override;
	
};
