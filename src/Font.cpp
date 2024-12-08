#include "Font.hpp"
#include "SFML/Graphics/Font.hpp"
#include "components/FileLoader.hpp"

loading<sf::Font> Font::Default = FileLoader::Instance().addFontToUpload("C:/Windows/Fonts/arial.ttf").get();
loading<sf::Font> Font::Jersey10 = FileLoader::Instance().addFontToUpload("fonts/Jersey10-Regular.ttf").get();
