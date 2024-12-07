#include "Font.hpp"
#include "components/FileLoader.hpp"

const sf::Font *const &Font::Default = FileLoader::Instance().addFontToUpload("C:/Windows/Fonts/arial.ttf");
