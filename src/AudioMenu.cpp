#include "AudioMenu.hpp"
#include "game/guns/Pistol.hpp"
#include <SFML/System.hpp>

AudioMenu::AudioMenu(sf::RenderWindow &window)
	: MenuBranch(window)
{}

void AudioMenu::start()
{
	player.setPosition(500, 500);
	player.start();
	player.setGun(Pistol(&player));
	enemy.setPosition(400, 400);
}

void AudioMenu::update()
{
	window.clear();
	player.update();
	enemy.update();

	Collidable::updateCollisionState();
	window.draw(enemy);
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
