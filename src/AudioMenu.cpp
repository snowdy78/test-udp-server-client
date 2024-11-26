#include "AudioMenu.hpp"
#include "game/EnemyShip.hpp"
#include "game/Ship.hpp"
#include "game/guns/Pistol.hpp"


AudioMenu::AudioMenu(sf::RenderWindow &window)
	: MenuBranch(window)
{}

void AudioMenu::start()
{
	field.append<Ship>();
	field.append<EnemyShip>();
	auto player = field[0];
	auto enemy	= field[1];
	player->setPosition(500, 500);
	player->setGun(Pistol(player));
	enemy->setPosition(400, 400);
	field.start();
}

void AudioMenu::update()
{
	window.clear();
	field.update();
	shader.load("space.frag", sf::Shader::Fragment);

	shader.setUniform("iResolution", rn::Vec2f(res));
	shader.setUniform<float>("iTime", clock.getElapsedTime().asMilliseconds()/1000.f);
	Collidable::updateCollisionState();
	
	window.draw(shader);
	window.draw(field);
	window.display();
}

void AudioMenu::onEvent(sf::Event &event)
{
	field.onEvent(event);
	if (event.type == sf::Event::Closed)
	{
		window.close();
	}
}
