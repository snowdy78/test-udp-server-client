#include "game/Gun.hpp"
#include "game/Ship.hpp"

Gun::~Gun() {}
Gun::Gun(const Ship *ship) : ship(ship) {}
void Gun::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (auto &iterator: bullets)
	{
		if (auto bullet = iterator.get())
		{
			target.draw(*bullet, states);
		}
	}
}
