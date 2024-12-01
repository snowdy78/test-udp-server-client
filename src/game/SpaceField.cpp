#include "game/SpaceField.hpp"

SpaceField::SpaceField() {}

SpaceField::SpaceField(const SpaceField &field)
{
	ships.resize(field.ships.size());
	for (size_t i = 0; i < field.ships.size(); ++i)
	{
		ships[i] = field.ships[i]->copy();
	}
}
SpaceField::~SpaceField()
{
	for (auto &ship: ships)
	{
		delete ship;
	}
}

void SpaceField::remove(AbstractShip *ship)
{
	auto it = std::find(ships.begin(), ships.end(), ship);
	if (it != ships.end())
	{
		delete *it;
		ships.erase(it);
	}
}
AbstractShip *SpaceField::get(size_t index)
{
	return ships.at(index);
}
AbstractShip *SpaceField::operator[](size_t index)
{
	return ships[index];
}
void SpaceField::start()
{
	for (auto &ship: ships)
	{
		ship->start();
	}
	mother.start();
}
void SpaceField::update()
{
	for (auto &ship: ships)
	{
		ship->update();
	}
	mother.update();
}
void SpaceField::onEvent(sf::Event &event)
{
	for (auto &ship: ships)
	{
		ship->onEvent(event);
	}
	mother.onEvent(event);
}
SpaceField::iterator SpaceField::begin()
{
	return ships.begin();
}
SpaceField::iterator SpaceField::end()
{
	return ships.end();
}
size_t SpaceField::size()
{
	return ships.size();
}
SpaceField::const_iterator SpaceField::cbegin() const
{
	return ships.cbegin();
}
SpaceField::const_iterator SpaceField::cend() const
{
	return ships.cend();
}

SpaceField::const_iterator SpaceField::begin() const
{
	return ships.begin();
}

SpaceField::const_iterator SpaceField::end() const
{
	return ships.end();
}

void SpaceField::clear()
{
	for (auto &ship: ships)
	{
		delete ship;
	}
	ships.clear();
}

void SpaceField::summonBullet(Bullet *const &bullet, const rn::Vec2f &direction)
{
	if (bullet)
	{
		bullet->setField(this);
		mother.summon(bullet, direction);
	}
}

void SpaceField::destroyBullet(const Bullet *const &bullet)
{
	mother.destroy(bullet);
}
void SpaceField::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto &iterator : mother)
	{
		if (auto bullet = iterator.get())
		{
			target.draw(*bullet, states);
		}
	}
	for (auto &ship: ships)
	{
		target.draw(*ship, states);
	}
}


SpaceField &SpaceField::operator=(const SpaceField &other)
{
	if (&other != this)
	{
		for (auto &ship: ships)
		{
			delete ship;
		}
		ships = other.ships;
	}
	return *this;
}
SpaceField &SpaceField::operator=(SpaceField &&other) noexcept
{
	if (&other != this)
	{
		for (auto &ship: ships)
		{
			delete ship;
		}
		ships = std::move(other.ships);
	}
	return *this;
}