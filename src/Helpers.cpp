#include "Helpers.hpp"

sf::SoundBuffer loadSound(const sf::String &file_name)
{
	sf::SoundBuffer sound_buffer;
	if (!sound_buffer.loadFromFile(file_name))
	{
		std::cerr << "Failed to load sound file 'shoot.ogg'" << std::endl;
		throw std::exception();
	}
	return std::move(sound_buffer);
}
std::ostream &operator<<(std::ostream &os, const sf::Vector2f &v)
{
	os << "Vector2( x:" << v.x << ", y:" << v.y << ")";
	return os;
}

std::ostream &operator<<(std::ostream &os, const sf::FloatRect &v)
{
	os << "FloatRect( x:" << v.left << ", y:" << v.top << ", w:" << v.width << ", h:" << v.height << ")";
	return os;
}

std::ostream &operator<<(std::ostream &os, const sf::View &v)
{
	os << "sf::View( cx:" << v.getCenter().x << ", cy:" << v.getCenter().y << ", w:" << v.getSize().x
	   << ", h:" << v.getSize().y << ")";
	return os;
}
bool everyTime(rn::Stopwatch &clock, const float t)
{
	if (clock.is_stopped())
		return false;
	if (clock.time<std::chrono::milliseconds>().count() % 1000 > t * 1000.f)
	{
		clock.stop();
		return true;
	}
	return false;
}
