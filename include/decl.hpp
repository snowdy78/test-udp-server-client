#pragma once
#include <RuneEngine/Engine.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/InputSoundFile.hpp>
#include <SFML/System.hpp>


class Font
{
public:
	inline static sf::Font Default = rn::sys::loadFont("C:\\Windows\\Fonts\\arial.ttf");
};
inline sf::Mutex mutex;


struct ChatSocket;
struct Client;
struct Server;

class RigitBody2d;
class Bullet;
class Ship;
class BulletMother;
class Gun;
class Collider;
class Collidable;
class PolygonCollider;
class EllipseCollider;
class AbstractShip;
class SpaceField;
class DamageDealer;
class Hittable;
