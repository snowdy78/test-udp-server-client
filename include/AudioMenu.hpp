#pragma once

#include "game/SpaceField.hpp"
#include "decl.hpp"

// audio distance playing


class AudioMenu : public rn::MenuBranch
{
	rn::Vec2u res = rn::VideoSettings::getResolution();
	SpaceField field;
	sf::Clock clock;
	rn::ShaderTexture shader{ res, "space.frag", sf::Shader::Fragment };
public:
	explicit AudioMenu(sf::RenderWindow &window);

	void start() override;
	void update() override;
	void onEvent(sf::Event &event) override;
};
