#include "Gun.hpp"
#include "Ship.hpp"

Gun::~Gun()
{}
Gun::Gun(const Ship *ship) : ship(ship)
{}
