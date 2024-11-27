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
void SpaceField::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto &ship: ships)
	{
		target.draw(*ship, states);
	}
}
void SpaceField::start()
{
	for (auto &ship: ships)
	{
		ship->start();
	}
}
void SpaceField::update()
{
	for (auto &ship: ships)
	{
		ship->update();
	}
}
void SpaceField::onEvent(sf::Event &event)
{
	for (auto &ship: ships)
	{
		ship->onEvent(event);
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
