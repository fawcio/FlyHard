/*
 * World.hpp
 *
 *  Created on: 16 lut 2015
 *      Author: slawek
 */

#ifndef GAME_WORLD_HPP_
#define GAME_WORLD_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "ResourceHolder.hpp"
#include "SceneNode.hpp"
#include "Aircraft.hpp"

namespace sfml_playground
{

class World: private sf::NonCopyable
{
public:
	explicit		World(sf::RenderWindow& window);
	virtual			~World();

	void			update();
	void 			draw();

private:
	void			loadTextures();
	void			buildScene();

private:
	enum class LayerID : std::size_t
	{
		eBackground,
		eAir,
		eLayerCount
	};

public:
	static const sf::Time cTimePerFrame;
	static const std::size_t cLayerCount = static_cast<std::size_t>(LayerID::eLayerCount);

private:


private:
	sf::RenderWindow&		mWindow;
	sf::View				mWorldView;
	TextureHolder			mTextures;
	SceneNode				mScenGraph;
	std::array<SceneNode*, cLayerCount> mSceneLayers;

	sf::FloatRect			mWorldBoudns;
	sf::Vector2f			mSpawnPosition;
	float					mScrollSpeed;
	Aircraft*				mPlayerAircraft;
};

} /* namespace sfml_playground */

#endif /* GAME_WORLD_HPP_ */
