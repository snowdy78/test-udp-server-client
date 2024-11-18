#include <RuneEngine/Engine.hpp>

#include "AudioMenu.hpp"
#include "ChatSocket.hpp"
#include "Client.hpp"
#include "Server.hpp"


int main()
{
	sf::RenderWindow window{
		{ 1920, 1080 },
		"window"
	};

	rn::MenuBranch::start_branch<AudioMenu>(window);
	return 0;
}
