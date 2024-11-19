#include "game/BulletMother.hpp"
#include "game/Bullet.hpp"


BulletMother::ChildBullet::ChildBullet(BulletMother *mother, Bullet *bullet) : mother(mother), bullet(bullet) {}

void BulletMother::ChildBullet::update()
{
	if (bullet && mother)
	{
		if (rn::math::length(mother->getPosition() - bullet->getPosition())
			> static_cast<float>(2 * rn::VideoSettings::getResolution().x))
		{
			need_to_remove = true;
		}
		else
			bullet->update();
	}
}

const Bullet *BulletMother::ChildBullet::get() const
{
	return bullet.get();
}
BulletMother::BulletMother() {}

void BulletMother::summon(Bullet *bullet, const rn::Vec2f &direction)
{
	bullet->setDirection(direction);
	bullets.emplace_back(this, bullet);
}
void BulletMother::update()
{
	using namespace std::ranges;
	std::vector<std::vector<ChildBullet>::iterator> remove_bullet_stack{};
	for (auto bullet = bullets.begin(); bullet != bullets.end(); bullet++)
	{
		bullet->update();
		if (bullet->need_to_remove)
			remove_bullet_stack.push_back(bullet);
	}

	for (auto &iterator: remove_bullet_stack)
	{
		bullets.erase(iterator);
	}
}
