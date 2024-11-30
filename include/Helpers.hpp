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
