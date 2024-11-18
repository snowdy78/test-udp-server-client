#pragma once

#include <vector>
#include "Bullet.hpp"
#include "decl.hpp"


class BulletMother
{
	class ChildBullet
	{
		Bullet *bullet;
		const BulletMother *mother;
		friend class BulletMother;

	public:
		ChildBullet()
		{
			bullet = new Bullet();
		}
		void update()
		{}
		void onCollide()
		{
			delete bullet;
			bullet = nullptr;
		}
	};

public:
	sf::Transform transform;
	BulletMother();
};
