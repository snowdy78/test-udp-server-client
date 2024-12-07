#include "Font.hpp"
#include "SFML/Graphics/Font.hpp"
#include "components/FileLoader.hpp"

const sf::Font *const &Font::Default = FileLoader::Instance().addFontToUpload("C:/Windows/Fonts/arial.ttf");
const sf::Font *const &Font::Jersey10 = FileLoader::Instance().addFontToUpload("C:/Windows/Fonts/Jersey10-Regular.ttf");
