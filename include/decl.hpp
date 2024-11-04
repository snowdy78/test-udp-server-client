#pragma once
#include <RuneEngine/Engine.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio/InputSoundFile.hpp>

namespace fonts
{
	inline sf::Font roboto = rn::sys::loadFont("Roboto-Regular.ttf");

}
struct ChatSocket;
struct Client;
struct Server;
