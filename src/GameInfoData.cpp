#include "GameInfoData.hpp"
#include "Font.hpp"

GameInfoData::GameInfoData(const sf::String &name, std::function<sf::String()> get_data)
	: name(name), get_data(get_data)
{
	text.setFont(Font::Default);
	updateData();
}

void GameInfoData::updateData()
{
	text.setString(name + ": " + get_data());
}

sf::String GameInfoData::getData() const
{
	return get_data();
}

const sf::String &GameInfoData::getName() const
{
	return name;
}

const sf::String &GameInfoData::getString() const
{
	return text.getString();
}

void GameInfoData::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(text, states);
}
