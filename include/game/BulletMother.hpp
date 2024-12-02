#pragma once

#include <vector>
#include "decl.hpp"
#include "game/Bullet.hpp"


class BulletMother : public sf::Transformable, public rn::LogicalObject
{
public:
	class ChildBullet : public rn::LogicalObject
	{
		friend class BulletMother;

	public:

		inline constexpr static float life_time_ms = 1000.f;

		std::unique_ptr<Bullet> bullet = nullptr;
		bool need_to_remove = false;
		BulletMother *mother;
		rn::Stopwatch clock;

		ChildBullet(BulletMother *mother, Bullet *bullet);
		const Bullet *get() const;
		bool isOutsideViewArea() const;
		void start() override;
		void update() override;
		void onEvent(sf::Event &event) override;
	};

private:
	std::vector<ChildBullet> bullets;

public:
	BulletMother();
	using iterator		 = std::vector<ChildBullet>::iterator;
	using const_iterator = std::vector<ChildBullet>::const_iterator;

	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;
	const_iterator begin() const;
	const_iterator end() const;
	size_t bulletCount() const;
	static sf::FloatRect getViewArea();
	void destroy(const Bullet *bullet);
	void summon(Bullet *bullet, const rn::Vec2f &direction);
	void start() override;
	void update() override;
	void onEvent(sf::Event &event) override;
};
