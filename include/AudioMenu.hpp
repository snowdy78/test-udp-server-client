#pragma once
#include "game/Ship.hpp"
#include "game/EnemyShip.hpp"
#include "decl.hpp"

// audio distance playing


class AudioMenu : public rn::MenuBranch
{
	Ship player{};
	EnemyShip enemy{};
public:
	explicit AudioMenu(sf::RenderWindow &window);

	void start() override;
	void update() override;
	void onEvent(sf::Event &event) override;
};
