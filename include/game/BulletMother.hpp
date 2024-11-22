#pragma once

#include <vector>
#include "game/Bullet.hpp"
#include "decl.hpp"


class BulletMother : public sf::Transformable, public rn::LogicalObject
{
	class ChildBullet : public rn::LogicalObject
	{
		std::unique_ptr<Bullet> bullet = nullptr;
		BulletMother *mother;
		friend class BulletMother;
		bool need_to_remove = false;

	public:
		ChildBullet(BulletMother *mother, Bullet *bullet);
		const Bullet *get() const;
		void start() override;
		/**
		* Updates the state of the ChildBullet. If the bullet is too far from its
		* mother, it marks itself for removal. Otherwise, it updates the bullet's state.
		*/
		void update() override;
		void onEvent(sf::Event &event) override;
	};

protected:
	std::vector<ChildBullet> bullets;

public:
	BulletMother();

	void summon(Bullet *bullet, const rn::Vec2f &direction);
	void start() override;
	void update() override;
	void onEvent(sf::Event &event) override;
};
