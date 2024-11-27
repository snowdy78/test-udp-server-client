#include "game/Gun.hpp"
#include "Helpers.hpp"
#include "game/AbstractShip.hpp"


Gun::~Gun() {}
void Gun::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (auto &iterator: bullets)
	{
		if (auto bullet = iterator.get())
		{
			target.draw(*bullet, states);
		}
	}
}
void Gun::setClearSoundDistance(float distance)
{
	sound.setClearSoundDistance(distance);
}
void Gun::setDisperseRadius(float radius)
{
	sound.setDisperseRadius(radius);
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
	if (ship)
	{
		summon(createBullet(), rn::math::norm(getTrajectory()));
		sound.play();
	}
}

bool Gun::hasRollback() const
{
	return has_rollback;
}

void Gun::update()
{
	BulletMother::update();
	if (everyTime(clock, getMillisDelay()))
	{
		clock.reset();
		has_rollback = false;
	}
}

float Gun::getMillisDelay() const
{
	return 300.f;
}
