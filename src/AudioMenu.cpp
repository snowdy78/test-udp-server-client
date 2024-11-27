#include "AudioMenu.hpp"
#include "game/EnemyShip.hpp"
#include "game/Ship.hpp"
#include "game/guns/Pistol.hpp"


AudioMenu::AudioMenu(sf::RenderWindow &window)
	: MenuBranch(window)
{
	th.reset(new sf::Thread([this]() { updateObjectsState(); }));
}

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
	th->launch();
	shader.load("space.frag", sf::Shader::Fragment);
	shader.setUniform("iResolution", rn::Vec2f(res));
	shader.setUniform("iTime", clock.getElapsedTime().asMilliseconds() / 1000.f);
	shader.setUniform("iPosition", field[0]->getPosition());
	shader.render();
	th->wait();
	window.draw(shader);
	window.draw(field);
	window.display();
}

void AudioMenu::onEvent(sf::Event &event)
{
	field.onEvent(event);
	if (event.type == sf::Event::Closed)
	{
		delete th.release();
		window.close();
	}
}
void AudioMenu::updateObjectsState()
{
	field.update();
	Collidable::updateCollisionState();
}
