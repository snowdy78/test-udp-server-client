#pragma once

#include "SoundDisperseEntity.hpp"
#include "decl.hpp"

class Bullet : public rn::MonoBehaviour
{
	inline static rn::StaticTexture texture{ "img/bullet_shoot.png" };
	inline static sf::SoundBuffer sound_buffer;
	inline static SoundDisperseEntity sound{ 200.f, 1000.f, &sound_buffer };
	sf::Sprite sprite;

	float mass		   = 0.100f;
	float velocity	   = 0.1f;
	float acceleration = 0.1f;
	rn::Vec2f direction{};

public:
	Bullet();

	void update() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
