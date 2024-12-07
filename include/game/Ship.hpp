#pragma once

#include "AbstractShip.hpp"
#include "Camera2d.hpp"
#include "components/FileLoader.hpp"
#include "decl.hpp"


class Ship : public AbstractShip
{
	inline static const sf::Texture *const &texture = FileLoader::Instance().addTextureToUpload("img/ship.png");
	Camera2d *camera = nullptr;

public:
	/**
	 * \brief Constructor for Ship
	 *
	 * Construct a Ship object with the image set to the contents of Ship::texture
	 */
	Ship(Camera2d * = nullptr);
	~Ship() override = default;

	void rotation() override;
	void movement() override;
	void onMove() override;
	void onEvent(sf::Event &event) override;
	void onRotation() override;
	void onHit() override;
	AbstractShip *copy() const override;
};
