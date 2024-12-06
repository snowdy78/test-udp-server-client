#pragma once

#include "components/GameInfo.hpp"
#include "decl.hpp"
#include "game/Camera2d.hpp"
#include "game/SpaceField.hpp"


// audio distance playing

class AudioMenu : public rn::MenuBranch
{
	
	class Background : public rn::MonoBehaviour
	{
		rn::Vec2u res = rn::VideoSettings::getResolution();
		rn::ShaderTexture shader{ res, "space.frag", sf::Shader::Fragment };
		sf::Clock clock;

	public:
		Background() {}
		template<class T>
		void setUniform(const sf::String &name, const T &value);

		void start() override;
		void update() override;
		void onEvent(sf::Event &event) override;
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	};
	class ShipCamera : public Camera2d
	{
		sf::RenderTarget &target;
		std::function<void()> update_on_move;

	public:
		ShipCamera(sf::RenderTarget &target, std::function<void()> update_on_move);
		virtual void onCameraMove() override;
	};
	Background background{};
	GameInfo info;
	std::unique_ptr<sf::Thread> th;
	AbstractShip *player = nullptr;
	std::unique_ptr<ShipCamera> camera = nullptr;
	SpaceField field;

	rn::Stopwatch fps_clock;
	bool dev_mode = true;

public:
	explicit AudioMenu(sf::RenderWindow &window);

	void start() override;
	void updateObjectsState();
	void summonShip();
	void update() override;
	void onEvent(sf::Event &event) override;
};
template<class T>
void AudioMenu::Background::setUniform(const sf::String &name, const T &value)
{
	shader.setUniform(name, value);
}
