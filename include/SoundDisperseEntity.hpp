#pragma once
#include "decl.hpp"

class SoundDisperseEntity : public sf::Sound
{
	float clear_dist, disperse_force = 50.f;
	using Sound::setVolume;
public:
	explicit SoundDisperseEntity(float clear_sound_distance = 0.f, float disperse_force = 1000.f, const sf::SoundBuffer *buffer = nullptr);

	float getClearSoundDistance() const;

	virtual void onPlay() {}
	virtual void onStop() {}
	virtual void onPause() {}
	void play()
	{
		sf::Sound::play();
		onPlay();
	}
	void stop()
	{
		Sound::stop();
		onStop();
	}
	void pause()
	{
		Sound::pause();
		onPause();
	}
	float getDisperseForce() const;

	float relativeVolume(const rn::Vec2f &point) const;
};
