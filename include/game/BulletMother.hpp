#pragma once

#include <vector>
#include "Bullet.hpp"
#include "decl.hpp"


class BulletMother : public sf::Transformable, public rn::LogicalObject
{
	class ChildBullet
	{
		Bullet *bullet;
		BulletMother *mother;
		friend class BulletMother;
		void remove();

	public:
		ChildBullet(BulletMother *mother, Bullet *bullet);
		ChildBullet(const ChildBullet &bullet) : bullet(bullet.bullet), mother(bullet.mother) {

		}
		~ChildBullet();
		const sf::Sprite *getSprite() const;
		void update();
		void onCollide();
	};

protected:
	std::vector<ChildBullet> bullets;

public:
	BulletMother();

	void summon(Bullet *bullet, const rn::Vec2f &direction);
	void update() override;
};
