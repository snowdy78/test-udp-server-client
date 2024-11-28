#pragma once

#include "decl.hpp"
#include "AbstractShip.hpp"
#include "BulletMother.hpp"
#include "SpaceFieldObject.hpp" 

template<class T>
concept ShipT = std::is_base_of<AbstractShip, T>::value && !std::is_same<T, AbstractShip>::value;

class SpaceField : public sf::Drawable, public rn::LogicalObject
{
	std::vector<AbstractShip *> ships{};
	BulletMother mother{};

public:
	using iterator		 = std::vector<AbstractShip *>::iterator;
	using const_iterator = std::vector<AbstractShip *>::const_iterator;

	SpaceField();
	SpaceField(const SpaceField &field);
	SpaceField(SpaceField &&) noexcept = default;
	~SpaceField();

	void start() override;
	void update() override;
	void onEvent(sf::Event &event) override;

	AbstractShip *get(size_t index);
	AbstractShip *operator[](size_t index);
	iterator begin();
	iterator end();
	size_t size();

	const_iterator cbegin() const;
	const_iterator cend() const;
	const_iterator begin() const;
	const_iterator end() const;
	void clear();

	template<ShipT T>
	void appendShip();
	void summonBullet(Bullet *const &bullet, const rn::Vec2f &direction);
	void destroyBullet(const Bullet *const &bullet);

	void remove(AbstractShip *ship);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	SpaceField &operator=(const SpaceField &other);
	SpaceField &operator=(SpaceField &&other) noexcept;
};


template<ShipT T>
void SpaceField::appendShip()
{
	T *ship = new T();
	ship->setField(this);
	ships.push_back(ship);
}
