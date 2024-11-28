#include "game/Gun.hpp"
#include "Helpers.hpp"
#include "game/AbstractShip.hpp"
#include "game/SpaceField.hpp"

Gun::~Gun() {}

void Gun::setClearSoundDistance(float distance)
{
	sound.setClearSoundDistance(distance);
}
void Gun::setDisperseRadius(float radius)
{
	sound.setDisperseRadius(radius);
}
void Gun::startRollback()
{
	has_rollback = true;
	clock.start();
}
Gun::Gun(const AbstractShip *user, const sf::SoundBuffer *buffer)
	: ship(user)
{
	if (buffer)
	{
		sound.setBuffer(*buffer);
	}
};

void Gun::shoot(const rn::Vec2f &direction)
{
	if (ship && ship->field && !has_rollback)
	{
		ship->field->summonBullet(createBullet(), rn::math::norm(getTrajectory()));
		sound.play();
		startRollback();
	}
}

bool Gun::hasRollback() const
{
	return has_rollback;
}

void Gun::update()
{
	if (everyTime(clock, getMillisDelay()))
	{
		clock.reset();
		has_rollback = false;
	}
}

float Gun::getMillisDelay() const
{
	return 0.3f;
}
