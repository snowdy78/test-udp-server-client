#include "game/bullets/BaseBullet.hpp"

BaseBullet::BaseBullet() = default;
Bullet *BaseBullet::copy() const
{
	return new BaseBullet();
}
