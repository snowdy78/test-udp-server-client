#pragma once
#include "game/Ship.hpp"
#include "game/EnemyShip.hpp"
#include "decl.hpp"

// audio distance playing


class AudioMenu : public rn::MenuBranch
{
	std::unique_ptr<Ship> player{new Ship()};
	std::unique_ptr<EnemyShip> enemy{new EnemyShip()};
public:
	explicit AudioMenu(sf::RenderWindow &window);

	void start() override;
	void update() override;
	void onEvent(sf::Event &event) override;
};
