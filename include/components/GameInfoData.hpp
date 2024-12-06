#pragma once

#include <RuneEngine/Engine.hpp>

class GameInfoData : public sf::Drawable, public sf::Transformable
{
    sf::String name;
    sf::Text text;
    std::function<sf::String()> get_data;
public:
    GameInfoData(const sf::String &name, std::function<sf::String()> get_data);

    void updateData();
    const sf::String &getString() const;
    sf::String getData() const;
    const sf::String &getName() const;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
