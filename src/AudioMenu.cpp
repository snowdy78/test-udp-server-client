#include "AudioMenu.hpp"
#include "RuneEngine/SettingsFile.hpp"
#include "game/EnemyShip.hpp"
#include "game/Ship.hpp"


AudioMenu::AudioMenu(sf::RenderWindow &window)
	: MenuBranch(window)
{
	th.reset(new sf::Thread([this]() {
		updateObjectsState();
	}));
}

void AudioMenu::start()
{
	field.appendShip<Ship>();
	player = field[0];
	player->setPosition(500, 500);
	summonShip();
	shader.load("space.frag", sf::Shader::Fragment);
	shader.setUniform("iResolution", rn::Vec2f(res));

	field.start();
}

void AudioMenu::update()
{
	window.clear();
	th->launch();
	shader.setUniform("iTime", clock.getElapsedTime().asMilliseconds() / 1000.f);
	if (player)
	{
		shader.setUniform("iPosition", player->getPosition());
	}
	shader.render();
	th->wait();
	window.draw(shader);
	window.draw(field);
	window.display();
}

void AudioMenu::onEvent(sf::Event &event)
{
	if (window.hasFocus())
	{
		field.onEvent(event);
	}
	if (event.type == sf::Event::Closed)
	{
		delete th.release();
		window.close();
	}
	if (dev_mode)
	{
		if (rn::isKeydown(sf::Keyboard::P))
		{
			summonShip();
		}
	}
}
void AudioMenu::updateObjectsState()
{
	if (!window.hasFocus())
	{
		return;
	}
	field.update();
	Collidable::updateCollisionState();
}

void AudioMenu::summonShip()
{
	auto res = rn::Vec2f(rn::VideoSettings::getResolution());
	field.appendShip<EnemyShip>();
	auto ship = dynamic_cast<EnemyShip *>(field[field.size() - 1]);
	if (ship)
	{
		ship->setTarget(player);
		ship->setPosition(rn::random::real(0.f, 1.f) * res.x, rn::random::real(0.f, 1.f) * res.y);
	}
}
