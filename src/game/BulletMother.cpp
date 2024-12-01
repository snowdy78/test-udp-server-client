#include "game/BulletMother.hpp"

BulletMother::ChildBullet::ChildBullet(BulletMother *mother, Bullet *bullet)
	: mother(mother),
	  bullet(bullet)
{}

void BulletMother::ChildBullet::update()
{
	using rn::math::length;
	if (bullet && mother)
	{
		if (!sf::FloatRect({}, rn::Vec2f(rn::VideoSettings::getResolution())).contains(bullet->getPosition()))
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

BulletMother::iterator BulletMother::begin()
{
	return bullets.begin();
}

BulletMother::iterator BulletMother::end()
{
	return bullets.end();
}

BulletMother::const_iterator BulletMother::cbegin() const
{
	return bullets.cbegin();
}

BulletMother::const_iterator BulletMother::cend() const
{
	return bullets.cend();
}

BulletMother::const_iterator BulletMother::begin() const
{
	return bullets.begin();
}

BulletMother::const_iterator BulletMother::end() const
{
	return bullets.end();
}

size_t BulletMother::bulletCount() const { return bullets.size(); }

void BulletMother::summon(Bullet *bullet, const rn::Vec2f &direction)
{
	bullet->setDirection(direction);
	bullets.emplace_back(this, bullet);
}
void BulletMother::update()
{
	std::vector<iterator> remove_bullet_stack{};
	for (auto child_bullet = bullets.begin(); child_bullet != bullets.end(); child_bullet++)
	{
		child_bullet->update();
		if (child_bullet->need_to_remove)
			remove_bullet_stack.push_back(child_bullet);
	}

	for (auto &iterator: remove_bullet_stack)
	{
		bullets.erase(iterator);
	}
}
void BulletMother::ChildBullet::start()
{
	if (bullet)
		bullet->start();
}
void BulletMother::ChildBullet::onEvent(sf::Event &event)
{
	if (bullet)
		bullet->onEvent(event);
}

void BulletMother::start()
{
	for (auto &iterator: bullets)
	{
		iterator.start();
	}
}

void BulletMother::onEvent(sf::Event &event)
{
	for (auto &iterator: bullets)
	{
		iterator.onEvent(event);
	}
}

void BulletMother::destroy(const Bullet *bullet)
{
	auto it = std::ranges::find_if(bullets, [&](const ChildBullet &blt) {
		return blt.get() == bullet;
	});
	if (it != bullets.end())
	{
		bullets.erase(it);
	}
}
