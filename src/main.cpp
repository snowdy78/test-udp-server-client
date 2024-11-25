#include <RuneEngine/Engine.hpp>

#include "AudioMenu.hpp"


int main()
{
	auto resolution = rn::VideoSettings::getResolution();
	sf::RenderWindow window{
		{ resolution.x, resolution.y },
		"window"
	};

	rn::MenuBranch::start_branch<AudioMenu>(window);
	return 0;
}
