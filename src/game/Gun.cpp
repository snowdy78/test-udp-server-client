#include "game/Gun.hpp"
#include "game/AbstractShip.hpp"

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
Gun::Gun(const AbstractShip *user, const sf::SoundBuffer *buffer)
	: ship(user)
{
	if (buffer)
	{
		sound.setBuffer(*buffer);
	}
};
