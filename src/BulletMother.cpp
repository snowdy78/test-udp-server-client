#include "BulletMother.hpp"

BulletMother::BulletMother()
{}

void BulletMother::update()
{
    for (auto &bullet : bullets)
    {
        bullet.update();
    }
}
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
BulletMother::ChildBullet::ChildBullet(BulletMother *mother) : mother(mother)
{
}
BulletMother::ChildBullet::~ChildBullet()
{
}
void BulletMother::ChildBullet::update()
{
    if (rn::math::length(mother->getPosition() - bullet->getPosition())
        > static_cast<float>(2 * rn::VideoSettings::getResolution().x))
    {
        remove();
    }
    bullet->update();
}
void BulletMother::ChildBullet::onCollide()
{
	remove();
}
void BulletMother::summon(rn::Vec2f direction)
{
    bullets.emplace_back(this);
}
