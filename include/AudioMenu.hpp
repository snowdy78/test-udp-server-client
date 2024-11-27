#pragma once

#include "game/SpaceField.hpp"
#include "decl.hpp"

// audio distance playing


class AudioMenu : public rn::MenuBranch
{
	rn::Vec2u res = rn::VideoSettings::getResolution();
	SpaceField field;
	std::unique_ptr<sf::Thread> th;
	sf::Mutex mutex;
	sf::Clock clock;
	AbstractShip *player = nullptr;
	rn::ShaderTexture shader{ res, "space.frag", sf::Shader::Fragment };

	bool dev_mode = true;
public:
	explicit AudioMenu(sf::RenderWindow &window);

	void start() override;
	void updateObjectsState();
	void summonShip();
	void update() override;
	void onEvent(sf::Event &event) override;
};
