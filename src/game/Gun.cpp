#include "game/Gun.hpp"
#include "game/Ship.hpp"

Gun::~Gun() {}
Gun::Gun(const Ship *ship) : ship(ship) {}
void Gun::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
    std::cout << bullets.size() << " - size\n";
	for (auto &bullet: bullets)
	{
		if (auto sprite = bullet.getSprite())
		{
			target.draw(*sprite, states);
		}
	}
}
