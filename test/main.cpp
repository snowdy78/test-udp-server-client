#include <catch2/catch_test_macros.hpp>
#include "game/Collidable.hpp"
#include "game/Collider.hpp"

class MyCollidable : public Collidable
{
    EllipseCollider collider;
public:
    using Collidable::updateCollisionState;
    
};

TEST_CASE("my test of test", "[single-file]")
{
    MyCollidable collidable;
	REQUIRE();
}
