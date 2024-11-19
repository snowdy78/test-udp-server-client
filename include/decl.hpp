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


struct ChatSocket;
struct Client;
struct Server;

class AbstractSpaceField;

class RigitBody2d;
class Bullet;
class Ship;
class BulletMother;
class Gun;
class Collider;

template<class T>
concept ColliderType = std::is_base_of<Collider, T>::value;

template<ColliderType T>
class CollidableObject;
class PolygonCollider;
class EllipseCollider;
