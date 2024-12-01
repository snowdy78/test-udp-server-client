#include "game/BulletMother.hpp"
#include "RuneEngine/Math/rectangle.hpp"

BulletMother::ChildBullet::ChildBullet(BulletMother *mother, Bullet *bullet, bool ignore_view_area)
	: mother(mother),
	  bullet(bullet),
	  ignore_view_area(ignore_view_area)
{}

void BulletMother::ChildBullet::update()
{
	using rn::math::length;
	if (bullet && mother)
	{
		if (!ignore_view_area && isOutsideViewArea())
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
sf::FloatRect BulletMother::getViewArea()
{
	return { {}, rn::Vec2f(rn::VideoSettings::getResolution()) };
}
bool BulletMother::ChildBullet::isOutsideViewArea() const
{
	return !BulletMother::getViewArea().contains(bullet->getPosition());
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

size_t BulletMother::bulletCount() const
{
	return bullets.size();
}

void BulletMother::summon(Bullet *bullet, const rn::Vec2f &direction)
{
	if (!bullet)
		return;

	bool ignore_view_area = false;
	rn::math::rectangle view_area(getViewArea());
	bullet->setDirection(direction);

	if (!view_area.contains(bullet->getPosition())) // if view area contains the bullet
	{
		rn::math::ray ray{ bullet->getPosition(), bullet->getDirection() }; // try to march the ray into the view area
		auto intersection_state = view_area.intersect(ray);
		if (!intersection_state) // if not intersect with the view area
		{
			delete bullet; // delete the bullet - it never be shown anyway
			return;
		}

		ignore_view_area = true;
	}
	bullets.emplace_back(this, bullet, ignore_view_area);
}
void BulletMother::update()
{
	std::vector<const_iterator> remove_bullet_stack{};
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
