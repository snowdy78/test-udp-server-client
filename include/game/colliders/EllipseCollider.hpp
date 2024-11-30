#pragma once

#include "game/Collider.hpp"

class EllipseCollider : public Collider
{
	rn::math::ellipce shape;

public:
	using shape_t = rn::math::ellipce;
	EllipseCollider()
		: shape(rn::Circle())
	{}
	EllipseCollider(const rn::math::ellipce &ellipse)
		: shape(ellipse)
	{}
	void transform(const rn::math::ellipce &ellipse);
	virtual bool collide(const PolygonCollider &collider) const override;
	virtual bool collide(const EllipseCollider &collider) const override;
	const rn::math::shape &getColliderShape() const override;
	Collider *copy() const override;
	sf::Drawable *toDrawable() const override;
};
