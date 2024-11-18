#include "Bullet.hpp"
#include "RigitBody2d.hpp"

/**
 * \brief Default constructor for Bullet
 *
 * Construct a Bullet object with the image set to the contents of Bullet::texture
 */
Bullet::Bullet() 
    : RigitBody2d(*texture) 
{

}
