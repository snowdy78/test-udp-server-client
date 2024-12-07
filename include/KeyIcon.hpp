#pragma once

#include <RuneEngine/Engine.hpp>

class KeyIcon : public rn::MonoBehaviour
{
    static std::map<sf::Keyboard::Key, char> key_map;
    static const sf::Texture *const &key_texture;
    static sf::Color color;
    sf::Keyboard::Key key;
    sf::Sprite sprite;
    sf::Text *key_text;
public:
    KeyIcon(sf::Keyboard::Key key);
    KeyIcon(const KeyIcon &icon);
    KeyIcon(KeyIcon &&icon);

	bool isIntersected(const rn::Vec2f &point) const override;

	~KeyIcon();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	KeyIcon &operator=(const KeyIcon &icon);
    KeyIcon &operator=(KeyIcon &&icon) noexcept;
};
