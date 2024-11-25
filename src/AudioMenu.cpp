#include "AudioMenu.hpp"
#include "game/guns/Pistol.hpp"

AudioMenu::AudioMenu(sf::RenderWindow &window)
	: MenuBranch(window)
{}

void AudioMenu::start()
{
	player->setPosition(500, 500);
	player->start();
	player->setGun(Pistol(player.get()));
	enemy->setPosition(400, 400);
	enemy->start();
}

void AudioMenu::update()
{
	window.clear();
	player->update();
	enemy->update();

	Collidable::updateCollisionState();
	window.draw(*enemy);
	window.draw(*player);
	window.display();
}

void AudioMenu::onEvent(sf::Event &event)
{
	player->onEvent(event);
	enemy->onEvent(event);
	if (event.type == sf::Event::Closed)
	{
		window.close();
	}
}
