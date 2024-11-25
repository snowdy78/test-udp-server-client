#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "game/Collidable.hpp"
#include "game/Collider.hpp"

class MyCollidable : public Collidable
{
	std::unique_ptr<Collider> collider;

public:
	MyCollidable(const Collider *collider)
		: collider(collider->copy())
	{}
	using Collidable::updateCollisionState;
	void set(float x, float y, float s)
	{
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
	bool resolve(const Collidable *collidable) const override
	{
		return true;
	}
	const Collider *getCollider() const override
	{
		return collider.get();
	}
};
enum CollisionState {
	Enter, Update, End, None
};
void requireCollisionState(MyCollidable &obj1, MyCollidable &obj2, CollisionState state)
{
	Collidable::updateCollisionState();
	bool is_enter = obj1.isCollisionEnter();
	bool is_update = obj1.isCollisionUpdate();
	bool is_end = obj1.isCollisionEnd();
	bool need_enter = is_enter && !is_update && !is_end;
	bool need_update = !is_enter && is_update && !is_end;
	bool need_end = !is_enter && !is_update && is_end;
	bool need_none = !is_enter && !is_update && !is_end;
	switch (state) {
		case Enter:
			REQUIRE( need_enter == true );
			break;
		case Update:
			REQUIRE( need_update == true );
			break;
		case End:
			REQUIRE( need_end == true );
			break;
		case None:
			REQUIRE( need_none == true );
			break;
	}
}
TEST_CASE("collision state test", "[single-file]")
{
	std::vector<std::shared_ptr<Collider>> colliders{ std::make_shared<EllipseCollider>(),
													  std::make_shared<PolygonCollider>() };


	

	for (auto &collider1: colliders)
	{
		MyCollidable obj1(collider1.get());
		obj1.set(0, 0, 20);
		for (auto &collider2: colliders)
		{
			MyCollidable obj2(collider2.get());
			const char *value1 = collider1 == colliders[0] ? "ellipse" : "polygon"; 
			const char *value2 = collider2 == colliders[0] ? "ellipse" : "polygon";
			CAPTURE(value1);
			CAPTURE(value2);

			obj2.set(0, 200, 20);

			requireCollisionState(obj1, obj2, None);
			obj2.set(0, 10, 20);

			requireCollisionState(obj1, obj2, Enter);

			requireCollisionState(obj1, obj2, Update);

			requireCollisionState(obj1, obj2, Update);

			obj2.set(200, 200, 20);
			
			requireCollisionState(obj1, obj2, End);

			
			requireCollisionState(obj1, obj2, None);
		}
	}
}
