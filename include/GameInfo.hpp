#pragma once

#include <RuneEngine/Engine.hpp>
#include "GameInfoData.hpp"

class GameInfo : public sf::Drawable, public sf::Transformable
{
	std::vector<GameInfoData> data{};
	rn::Grid table;
	bool visible = true;

	static rn::Vec2f getSampleSize();
	static size_t getRowCount();
    void updateText();
public:
	GameInfo();
	void addData(sf::String name, std::function<sf::String()> get_data);
	void setVisible(bool visible);
	bool isVisible() const;
	void removeData(size_t index);
    void removeData(const sf::String &name);
    void updateData(size_t index);
    void updateData(const sf::String &name);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
