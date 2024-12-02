#include "AudioMenu.hpp"


int main()
{
	auto resolution = rn::VideoSettings::getResolution();
	sf::RenderWindow window{
		{ resolution.x, resolution.y },
		"window"
	};
	window.setFramerateLimit(rn::VideoSettings::getFramerateLimit());
	window.setVerticalSyncEnabled(rn::VideoSettings::getVsync());
	window.setKeyRepeatEnabled(false);
	rn::MenuBranch::start_branch<AudioMenu>(window);
	return 0;
}
