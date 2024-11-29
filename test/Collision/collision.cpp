#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "game/Collidable.hpp"
#include "game/Collider.hpp"
#include "game/colliders/EllipseCollider.hpp"
#include "game/colliders/PolygonCollider.hpp"


class MyCollidable : public Collidable
{
	std::unique_ptr<Collider> collider = nullptr;

public:
	CollisionState state = None;
	MyCollidable(const Collider *collider_ptr)
	{
		collider.reset(collider_ptr->copy());
	}
	using Collidable::updateCollisionState;
	void set(float x, float y, float s)
	{
		state = None;
		if (auto e = dynamic_cast<EllipseCollider *>(collider.get()))
		{
			rn::Circle c(s);
			c.setPosition(x, y);
			e->transform(c);
		}
		else if (auto p = dynamic_cast<PolygonCollider *>(collider.get()))
		{
			rn::math::rectangle rect({ x, y }, { x + s, y + s });
			p->transform(rect);
		}
	}
	virtual void onCollisionEnter(Collidable *collidable) override
	{
		state = Enter;
	}
	virtual void onCollisionUpdate(Collidable *collidable) override
	{
		state = Update;
	}
	virtual void onCollisionEnd(Collidable *collidable) override
	{
		state = End;
	}
	bool resolve(const Collidable *collidable) const override
	{
		return true;
	}
	const Collider *getCollider() const override
	{
		return collider.get();
	}
};
void requireCollisionState(MyCollidable &obj1, MyCollidable &obj2, Collidable::CollisionState state)
{
	Collidable::updateCollisionState();
	bool state1 = obj1.state == state;
	bool state2 = obj2.state == state;	

	REQUIRE( state1 == true );
	REQUIRE( state2 == true );
}
TEST_CASE("collision state test1", "[single-file]")
{
	std::vector<std::shared_ptr<Collider>> colliders{ std::make_shared<EllipseCollider>(),
													  std::make_shared<PolygonCollider>() };

	for (auto &collider1 : colliders)
	{
		MyCollidable obj1(collider1.get());
		obj1.set(0, 0, 20);
		for (auto &collider2 : colliders)
		{
			MyCollidable obj2(collider2.get());
			const char *value1 = collider1 == colliders[0] ? "ellipse" : "polygon";
			const char *value2 = collider2 == colliders[0] ? "ellipse" : "polygon";
			CAPTURE(value1);
			CAPTURE(value2);

			obj2.set(0, 200, 20);

			requireCollisionState(obj1, obj2, Collidable::None);
			obj2.set(0, 10, 20);

			requireCollisionState(obj1, obj2, Collidable::Enter);

			requireCollisionState(obj1, obj2, Collidable::Update);

			requireCollisionState(obj1, obj2, Collidable::Update);

			obj2.set(200, 200, 20);

			requireCollisionState(obj1, obj2, Collidable::End);

			requireCollisionState(obj1, obj2, Collidable::None);
		}
	}
}
