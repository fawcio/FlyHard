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
	enum LayerID : std::size_t
	{
		eBackground,
		eAir,
		eForeground,
		eLayerCount
	};

public:
	static const sf::Time cTimePerFrame;

private:


private:
	sf::RenderWindow&		mWindow;
	sf::View				mWorldView;
	TextureHolder			mTextures;
	SceneNode				mScenGraph;
	std::array<SceneNode*, LayerID::eLayerCount> mSceneLayers;

	sf::FloatRect			mWorldBoudns;
	sf::Vector2f			mSpawnPosition;
	float					mScrollSpeed;
	SceneNode*				mPlayerAircraft;
};

} /* namespace sfml_playground */

#endif /* GAME_WORLD_HPP_ */
