#include <catch2/catch_test_macros.hpp>
#include "game/Collidable.hpp"
#include "game/Collider.hpp"

class MyCollidable : public Collidable
{
	Collider *collider;

public:
	using Collidable::updateCollisionState;
	void set(float x, float y, float r)
	{
		if (auto e = dynamic_cast<EllipseCollider *>(collider))
		{
			rn::Circle circle(r);
			circle.setPosition(x, y);
			e->transform(rn::math::ellipce(circle));
		}
		else if (auto p = dynamic_cast<PolygonCollider *>(collider))
		{
            p->transform(rn::math::polygon());
        }
	}
	bool resolve(const Collidable *collidable) const override
	{
		return true;
	}
	const Collider *getCollider() const override
	{
		return collider;
	}
};

TEST_CASE("my test of test", "[single-file]")
{
	MyCollidable collidable;
	collidable.set(0, 0, 20);
	MyCollidable collidable2;
	collidable2.set(0, 20, 20);

	CHECK(collidable.isCollisionEnter() == false);
	CHECK(collidable.isCollisionUpdate() == false);
	CHECK(collidable.isCollisionEnd() == false);

	collidable.updateCollisionState();
	collidable2.updateCollisionState();

	CHECK(collidable.isCollisionEnter() == true);
	CHECK(collidable.isCollisionUpdate() == false);
	CHECK(collidable.isCollisionEnd() == false);

	collidable.updateCollisionState();
	collidable2.updateCollisionState();

	CHECK(collidable.isCollisionEnter() == false);
	CHECK(collidable.isCollisionUpdate() == true);
	CHECK(collidable.isCollisionEnd() == false);

	collidable.updateCollisionState();
	collidable2.updateCollisionState();

	CHECK(collidable.isCollisionEnter() == false);
	CHECK(collidable.isCollisionUpdate() == true);
	CHECK(collidable.isCollisionEnd() == false);

	collidable2.set(20, 20, 20);
	collidable.updateCollisionState();
	collidable2.updateCollisionState();

	CHECK(collidable.isCollisionEnter() == false);
	CHECK(collidable.isCollisionUpdate() == false);
	CHECK(collidable.isCollisionEnd() == true);

	collidable.updateCollisionState();
	collidable2.updateCollisionState();

	CHECK(collidable.isCollisionEnter() == false);
	CHECK(collidable.isCollisionUpdate() == false);
	CHECK(collidable.isCollisionEnd() == false);
}
