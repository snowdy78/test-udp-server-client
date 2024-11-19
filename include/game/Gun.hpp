#pragma once


#include "BulletMother.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "decl.hpp"


class Gun : public BulletMother, public sf::Drawable
{
protected:
	static sf::SoundBuffer loadSound(const sf::String &file_name)
	{
		sf::SoundBuffer sound_buffer;
		if (!sound_buffer.loadFromFile(file_name))
		{
			std::cerr << "Failed to load sound file 'shoot.ogg'" << std::endl;
			throw std::exception();
		}
		return sound_buffer;
	}
	SoundDisperseEntity sound{ 20.f, 100.f };

	const Ship *ship;

	void setClearSoundDistance(float distance)
	{
		sound.setClearSoundDistance(distance);
	}
	void setDisperseRadius(float radius)
	{
		sound.setDisperseRadius(radius);
	}

public:
	Gun(const Ship *ship, const sf::SoundBuffer *buffer = nullptr);
	virtual ~Gun()								   = 0;
	virtual void shoot(const rn::Vec2f &direction) = 0;
	virtual Bullet *createBullet() const		   = 0;
	virtual Gun *copy() const					   = 0;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
