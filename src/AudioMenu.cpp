#include "AudioMenu.hpp"
#include "RuneEngine/SettingsFile.hpp"
#include "decl.hpp"
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
	camera.reset(new ShipCamera(window, background));
	field.appendShip<Ship>(camera.get());
	player = field[0];
	rn::Vec2f res{ rn::VideoSettings::getResolution() };
	player->setPosition(res / 2.f);
	summonShip();
	background.start();
	field.start();
	fps_clock.start();
}

void AudioMenu::update()
{
	window.clear();

	th->launch();
	background.update();
	th->wait();
	sf::Transform bg_transform;
	if (camera)
		bg_transform = camera->getTransform();
	window.draw(background, bg_transform);
	window.draw(field);
	window.display();
}

void AudioMenu::onEvent(sf::Event &event)
{
	background.onEvent(event);

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
		ship->start();
		ship->setTarget(player);
		if (camera)
		{
			rn::Vec2f randomPosition{
				rn::random::real(0.f, 1.f) * camera->getViewSize().x, 
				rn::random::real(0.f, 1.f) * camera->getViewSize().x
			};
			ship->setPosition(camera->getPosition() + randomPosition);
		}
	}
}

AudioMenu::ShipCamera::ShipCamera(sf::RenderTarget &target, Background &bg)
	: target(target), bg(bg)
{}

void AudioMenu::ShipCamera::onCameraMove()
{
	target.setView(getView());
	bg.setPosition(getPosition());
}

void AudioMenu::Background::start()
{
	shader.setUniform("iResolution", rn::Vec2f(res));
}

void AudioMenu::Background::update()
{
	shader.setUniform("iPosition", -getPosition());
	shader.setUniform("iTime", clock.getElapsedTime().asMilliseconds() / 1000.f);
}

void AudioMenu::Background::onEvent(sf::Event &event) {}

void AudioMenu::Background::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(shader, states);
}
