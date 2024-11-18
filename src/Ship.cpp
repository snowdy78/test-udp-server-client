#include "Ship.hpp"
#include "RigitBody2d.hpp"

/**
 * \brief Constructor for Ship
 *
 * Construct a Ship object with the image set to the contents of Ship::texture
 */
Ship::Ship() : RigitBody2d(*texture)
{}
