#pragma once
#include "Ship.hpp"
#include "SoundDisperseEntity.hpp"
#include "decl.hpp"

// audio distance playing


class AudioMenu : public rn::MenuBranch
{
	sf::SoundBuffer sound_buf;
	SoundDisperseEntity sound;
	class PlayButton : public rn::Button
	{
		sf::Sound *sound;

	public:
		PlayButton(sf::Sound *sound);

		static rn::Vec2f getSize();

		virtual void onClick();
		bool endPlaying()
		{
			return sound && sound->getPlayingOffset() == sound->getBuffer()->getDuration();
		}
		void onEvent(sf::Event &event);
	};
	PlayButton play_button{ &sound };
	Ship player{};

public:
	explicit AudioMenu(sf::RenderWindow &window);

	void start() override;
	void update() override;
	void onEvent(sf::Event &event) override;
};
