#pragma once
#include "decl.hpp"

class SoundDisperseEntity : public sf::Sound, public rn::LogicalObject
{
	float clear_dist, disperse_force = 50.f;
	using Sound::setVolume;
	float relativeVolume(const rn::Vec2f &point) const;
public:
	explicit SoundDisperseEntity(float clear_sound_distance = 0.f, float disperse_force = 1000.f, const sf::SoundBuffer *buffer = nullptr);

	float getClearSoundDistance() const;

	virtual void onPlay() {}
	virtual void onStop() {}
	virtual void onPause() {}
	void play();
	void stop();
	void pause();
	float getDisperseForce() const;
	/// Update the volume of the sound based on the relative distance from the listener
	void update() override;
};
