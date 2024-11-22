#include "game/Collider.hpp"

const rn::math::shape &PolygonCollider::getColliderShape() const
{
	return shape;
}
const rn::math::shape &EllipseCollider::getColliderShape() const
{
	return shape;
}

bool PolygonCollider::collide(const PolygonCollider &collider) const
{
	return shape.collide(collider.shape);
}

bool PolygonCollider::collide(const EllipseCollider &collider) const
{
	return shape.collide(static_cast<const rn::math::ellipce &>(collider.getColliderShape()));
}

bool EllipseCollider::collide(const PolygonCollider &collider) const
{
	return shape.collide(static_cast<const rn::math::polygon &>(collider.getColliderShape()));
}
void EllipseCollider::transform(rn::math::ellipce ellipse)
{
	shape = ellipse;
}
void PolygonCollider::transform(rn::math::polygon polygon)
{
	shape = polygon;
}
bool EllipseCollider::collide(const EllipseCollider &collider) const
{
	rn::Circle circle = rn::Circle(shape.r);
	circle.setScale(shape.a, shape.b);
	circle.setPosition(shape.center);
	circle.setOrigin(shape.origin);
	circle.setRotation(shape.rotation);
	circle.setPointCount(25);
	return rn::math::polygon(circle).collide(static_cast<const rn::math::ellipce &>(collider.getColliderShape()));
}
