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
		ChildBullet(BulletMother *mother);
		~ChildBullet();
		void update();
		void onCollide();
	};
	std::vector<ChildBullet> bullets;

public:
	BulletMother();

	void summon(rn::Vec2f direction);
	void update() override;
};
