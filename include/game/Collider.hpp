#pragma once

#include "decl.hpp"

class Collider : public sf::Transformable
{
protected:
	virtual const rn::math::shape &getColliderShape() const = 0;
public:
	virtual bool collide(const PolygonCollider &collider) const = 0;
	virtual bool collide(const EllipseCollider &collider) const = 0;
};
class PolygonCollider : public Collider
{
	rn::math::polygon shape;

public:
	PolygonCollider() {}
	PolygonCollider(rn::math::polygon shape) : shape(shape) {}

	virtual bool collide(const PolygonCollider &collider) const override;
	virtual bool collide(const EllipseCollider &collider) const override;
	void transform(rn::math::polygon polygon);
	const rn::math::shape &getColliderShape() const override;
};
class EllipseCollider : public Collider
{
	rn::math::ellipce shape;

public:
	EllipseCollider() : shape(rn::Circle()) {}
	EllipseCollider(rn::math::ellipce ellipse) : shape(ellipse) {}
	void transform(rn::math::ellipce ellipse);
	virtual bool collide(const PolygonCollider &collider) const override;
	virtual bool collide(const EllipseCollider &collider) const override;
	const rn::math::shape &getColliderShape() const override;
};
