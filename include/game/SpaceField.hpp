#pragma once

#include "AbstractShip.hpp"
#include "decl.hpp"


class SpaceField
{
	std::vector<AbstractShip *> ships{};

public:
	SpaceField() {}

	void append(AbstractShip *ship)
	{
		ships.push_back(ship);
	}

	void remove(AbstractShip *ship) {
        ships.erase(std::remove(ships.begin(), ships.end(), ship), ships.end());
    }
};
