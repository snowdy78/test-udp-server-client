#pragma once
#include <RuneEngine/Engine.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio/InputSoundFile.hpp>

class Font
{
public:
	inline static sf::Font Default = rn::sys::loadFont("C:\\Windows\\Fonts\\arial.ttf");

};
struct ChatSocket;
struct Client;
struct Server;
