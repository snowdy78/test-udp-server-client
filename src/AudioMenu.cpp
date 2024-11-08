#include "AudioMenu.hpp"

AudioMenu::PlayButton::PlayButton(sf::Sound *sound): Button(getSize(), "Play", fonts::roboto), sound(sound) {

}

rn::Vec2f AudioMenu::PlayButton::getSize() {
	rn::Vec2f res{rn::VideoSettings::getResolution()};
	return {res.x/14.f, res.y/20.f};
}

void AudioMenu::PlayButton::onClick() {
	if (sound)
	{
		if (sound->getBuffer())
		{
			if (sound->getStatus() == sf::Sound::Stopped || sound->getStatus() == sf::Sound::Paused)
			{
				sound->play();
				content.setString("Stop");
			}
			else if (sound->getStatus() == sf::Sound::Playing)
			{
				sound->pause();
				content.setString("Play");
			}
		}
	}
}

void AudioMenu::PlayButton::onEvent(sf::Event &event) {
	if (isClicked(sf::Mouse::Left))
	{
		onClick();
	}
}

AudioMenu::AudioMenu(sf::RenderWindow &window): MenuBranch(window) {

}

void AudioMenu::start()
{
	sound_buf.loadFromFile("Zero Sum.mp3");
	sound.setBuffer(sound_buf);
	sound.setRelativeToListener(true);
	player.setPosition(500, 500);
	player.start();
}

void AudioMenu::update()
{
	window.clear();
	player.update();
	sf::Listener::setGlobalVolume(sound.relativeVolume(player.getPosition()));
	window.draw(player);
	window.draw(play_button);
	window.display();
}

void AudioMenu::onEvent(sf::Event &event)
{
	player.onEvent(event);
	if (event.type == sf::Event::Closed)
	{
		window.close();
	}
	play_button.onEvent(event);
}
