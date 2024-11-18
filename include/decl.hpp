#pragma once
#include <RuneEngine/Engine.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/InputSoundFile.hpp>
#include <SFML/System.hpp>


class Font
{
public:
	inline static sf::Font Default = rn::sys::loadFont("C:\\Windows\\Fonts\\arial.ttf");
};
struct ChatSocket;
struct Client;
struct Server;
