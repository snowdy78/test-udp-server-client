#pragma once

#include "Collidable.hpp"
#include "SoundDisperseEntity.hpp"
#include "decl.hpp"

class Bullet : public rn::MonoBehaviour, public Collidable
{
	static sf::SoundBuffer loadSound() {
		sf::SoundBuffer sound_buffer;
		if (!sound_buffer.loadFromFile("shoot.ogg")) {
			std::cerr << "Failed to load sound file 'shoot.ogg'" << std::endl;
			throw std::exception();
		}
		return sound_buffer;
	}
	inline static rn::StaticTexture texture{ "img/bullet_shoot.png" };
	inline static sf::SoundBuffer sound_buffer = loadSound();
	SoundDisperseEntity sound{ 200.f, 1000.f };
	sf::Sprite sprite;

	float mass		   = 0.100f;
	float velocity	   = 0.1f;
	float acceleration = (0.2f - 0.1f) / 250.f;
	rn::Vec2f direction{};
	EllipseCollider collider;
	void updateCollider();
	
public:
	Bullet();
	~Bullet() override = 0;

	void setDirection(const rn::Vec2f &direction);
	void setMass(float mass);
	void setVelocity(float velocity);
	void setAcceleration(float acceleration);
	void setPosition(float x, float y);
	void setPosition(const rn::Vec2f &vector);
	void move(float x, float y);
	void move(const rn::Vec2f &p);

	const rn::Vec2f &getDirection() const;
	const sf::Sprite &getSprite() const;
	float getMass() const;
	float getVelocity() const;
	float getAcceleration() const;
	rn::Vec2f getSize() const;
	bool isIntersected(const rn::Vec2f &point) const override;
	const Collider *getCollider() const override;
	bool castToChild(const Collidable *collidable) const override;
	void update() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	virtual Bullet *copy() const = 0;
};
