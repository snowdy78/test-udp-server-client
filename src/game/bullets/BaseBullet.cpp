#include "game/bullets/BaseBullet.hpp"

BaseBullet::BaseBullet(const Gun *gun) : Bullet(gun), init_dmg(initial_damage) {}
Bullet *BaseBullet::copy() const
{
	return new BaseBullet(gun);
}
