#include "Gun.hpp"
#include "Ship.hpp"

Gun::~Gun()
{}
Gun::Gun(Ship *ship) : ship(ship)
{}
