#include "game/BulletMother.hpp"
#include "game/Bullet.hpp"

BulletMother::BulletMother() {}

void BulletMother::ChildBullet::remove()
{
	for (auto iter = mother->bullets.begin(); iter != mother->bullets.end(); ++iter)
	{
		if (&*iter == this)
		{
			mother->bullets.erase(iter);
			break;
		}
	}
}
BulletMother::ChildBullet::ChildBullet(BulletMother *mother, Bullet *bullet) : mother(mother), bullet(bullet) {}

BulletMother::ChildBullet::~ChildBullet()
{
	delete bullet;
}
void BulletMother::ChildBullet::update()
{
	if (rn::math::length(mother->getPosition() - bullet->getPosition())
		> static_cast<float>(2 * rn::VideoSettings::getResolution().x))
	{
		remove();
	}
	else
	{
		bullet->update();
	}
}
void BulletMother::ChildBullet::onCollide()
{
	remove();
}
void BulletMother::summon(Bullet *bullet, const rn::Vec2f &direction)
{
	bullet->setDirection(direction);
	bullets.emplace_back(this, bullet);
}
void BulletMother::update()
{
	for (auto &bullet: bullets)
	{
		bullet.update();
	}
}
const sf::Sprite *BulletMother::ChildBullet::getSprite() const
{
	if (bullet)
		return &bullet->getSprite();
	return nullptr;
}
