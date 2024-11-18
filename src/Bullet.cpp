#include "Bullet.hpp"
#include "RigitBody2d.hpp"

/**
 * \brief Default constructor for Bullet
 *
 * Construct a Bullet object with the image set to the contents of Bullet::texture
 */
Bullet::Bullet() : sprite(*texture)
{
	sound_buffer.loadFromFile("shoot.ogg");
}
void Bullet::update()
{
	sound.update();
}
void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
