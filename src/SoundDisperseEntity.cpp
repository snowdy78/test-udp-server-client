#include "SoundDisperseEntity.hpp"

SoundDisperseEntity::SoundDisperseEntity(float clear_sound_distance, float disperse_force,
	const sf::SoundBuffer *buffer)
	:
	clear_dist(clear_sound_distance),
	disperse_force(disperse_force)
{
	if (buffer)
	{
		setBuffer(*buffer);
	}
}

float SoundDisperseEntity::getClearSoundDistance() const {
	return clear_dist;
}

float SoundDisperseEntity::getDisperseForce() const {
	return disperse_force;
}

float SoundDisperseEntity::relativeVolume(const rn::Vec2f &point) const
{
	using namespace rn::math;
	rn::Vec2f pdist = rn::Vec2f{getPosition().x, getPosition().y} - point;
	auto dist       = length(pdist);
	if (dist < 0.00001f)
		return 100;
	return (1.0f - std::clamp((clear_dist + dist) / disperse_force, 0.f, 1.f)) * 100.f;
}
void SoundDisperseEntity::play() {
	sf::Sound::play();
	onPlay();
}
void SoundDisperseEntity::stop() {
	Sound::stop();
	onStop();
}
void SoundDisperseEntity::pause() {
	Sound::pause();
	onPause();
}
void SoundDisperseEntity::update() {
	setVolume(relativeVolume(
		{sf::Listener::getPosition().x, sf::Listener::getPosition().y}));
}
