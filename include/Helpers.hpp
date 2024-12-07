#pragma once

#include "decl.hpp"

sf::SoundBuffer loadSound(const sf::String &file_name);
/**
 * @brief if clock is running then it will check on every frame does it over rollback 
 * @param clock Stopwatch to check
 * @param t modulo value
 * @return True if delay is over and stop clock
 */
bool everyTime(rn::Stopwatch &clock, const float t);

std::ostream &operator<<(std::ostream &os, const sf::Vector2f &v);
std::ostream &operator<<(std::ostream &os, const sf::FloatRect &v);
std::ostream &operator<<(std::ostream &os, const sf::View &v);