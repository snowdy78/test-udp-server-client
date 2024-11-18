#include "Ship.hpp"
#include "Gun.hpp"
#include "RigitBody2d.hpp"

Ship::Ship() : RigitBody2d(*texture)
{}
void Ship::shoot()
{
	if (!gun)
	{
		return;
	}
	gun->shoot(RigitBody2d::getDirection2d());
}
