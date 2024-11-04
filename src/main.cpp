#include <RuneEngine/Engine.hpp>

#include "AudioMenu.hpp"
#include "ChatSocket.hpp"
#include "Server.hpp"
#include "Client.hpp"

int main()
{
    sf::RenderWindow window{{1920, 1080}, "window"};

    rn::MenuBranch::start_branch<AudioMenu>(window);
    return 0;
}
