#include "game/Camera2d.hpp"

sf::View Camera2d::getView() const
{
	return sf::View(getTransform().transformRect({ {}, size }));
}

Camera2d::Camera2d()
	: size(rn::VideoSettings::getResolution())
{}

void Camera2d::setPosition(const rn::Vec2f &v)
{
	sf::Transformable::setPosition(v);
	onCameraMove();
}


void Camera2d::setPosition(float x, float y)
{
	sf::Transformable::setPosition(x, y);
	onCameraMove();
}

void Camera2d::move(const rn::Vec2f &v)
{
	sf::Transformable::move(v);
	onCameraMove();
}

void Camera2d::move(float x, float y)
{
	sf::Transformable::move(x, y);
	onCameraMove();
}

rn::Vec2f Camera2d::getViewSize() const
{
	return size;
}
