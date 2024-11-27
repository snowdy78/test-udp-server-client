#include "Helpers.hpp"

sf::SoundBuffer loadSound(const sf::String &file_name)
{
    sf::SoundBuffer sound_buffer;
    if (!sound_buffer.loadFromFile(file_name))
    {
        std::cerr << "Failed to load sound file 'shoot.ogg'" << std::endl;
        throw std::exception();
    }
    return sound_buffer;
}