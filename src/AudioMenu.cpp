#include "AudioMenu.hpp"
#include "game/guns/Pistol.hpp"

AudioMenu::AudioMenu(sf::RenderWindow &window) : MenuBranch(window)
{}

void AudioMenu::start()
{
	player.setPosition(500, 500);
	player.start();
	player.setGun(Pistol(&player));
}

void AudioMenu::update()
{
	window.clear();
	Collidable::updateCollisionState();
	player.update();

	window.draw(player);
	window.display();
}

void AudioMenu::onEvent(sf::Event &event)
{
	player.onEvent(event);
	if (event.type == sf::Event::Closed)
	{
		window.close();
	}
}
