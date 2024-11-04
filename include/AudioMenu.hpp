#pragma once
#include "decl.hpp"
#include "RigitBody2d.hpp"
#include "SoundDisperseEntity.hpp"
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

		void onEvent(sf::Event &event);
	};
	PlayButton play_button{&sound};
	RigitBody2d player{{100, 100}};
public:
	explicit AudioMenu(sf::RenderWindow &window);

	void start() override;
	void update() override;
	void onEvent(sf::Event &event) override;
};

