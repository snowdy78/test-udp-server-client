#include "game/Gun.hpp"
#include "game/Ship.hpp"

Gun::~Gun() {}
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
Gun::Gun(const Ship *ship, const sf::SoundBuffer *buffer) : ship(ship)
{
	if (buffer)
	{
		sound.setBuffer(*buffer);
	}
};
