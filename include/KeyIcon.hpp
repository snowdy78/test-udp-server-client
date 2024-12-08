#pragma once

#include <RuneEngine/Engine.hpp>
#include "components/FileLoader.hpp"

class KeyIcon : public rn::MonoBehaviour
{
    using scancode_e = sf::Keyboard::Scancode;
public:
    using map_key_texture = std::map<scancode_e, const sf::Texture* const*>;
    using map_key_char = std::map<scancode_e, char>;
private:
    static map_key_char key_map;
    
    static loading<sf::Texture> key_sample_texture;

    static sf::Color color;
    static map_key_texture key_textures;
    scancode_e key;
    sf::Sprite sprite;
    sf::Text *key_text;
public:
    KeyIcon(scancode_e key);
    KeyIcon(const KeyIcon &icon);
    KeyIcon(KeyIcon &&icon);

	bool isIntersected(const rn::Vec2f &point) const override;

	~KeyIcon();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	KeyIcon &operator=(const KeyIcon &icon);
    KeyIcon &operator=(KeyIcon &&icon) noexcept;
};
