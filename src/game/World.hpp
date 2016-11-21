#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "resource_mgmt/ResourceHolder.hpp"
#include "entities/SceneNode.hpp"
#include "utils/Units.hpp"

namespace SFGame
{

/**
 * Forward declarations
 */
class CommandQueue;
class SceneNode;

class World: private sf::NonCopyable
{
public:
    explicit		World(sf::RenderWindow& window);
	virtual			~World();

	void			update();
	void 			draw();

	std::weak_ptr<CommandQueue> getCommandQueue() const { return mCommandQueue; }

    const sf::FloatRect& getWorldBounds() const { return mWorldBoudns; }

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

	static const Frequency	cFrameLimit;
	static const sf::Time	cTimePerFrame;
	static const float		cScrollSpeed;
	static const Speed		cScrollSpeed_;

	static const Length  cWorldWidth;

private:
	sf::RenderWindow&		mWindow;
	sf::View				mWorldView;
	TextureHolder			mTextures;
    SceneNode				mScenGraph;
	std::array<SceneNode*, LayerID::eLayerCount> mSceneLayers;

	sf::FloatRect			mWorldBoudns;
	sf::Vector2f			mSpawnPosition;
    SceneNode*				mPlayerAircraft;

	std::shared_ptr<CommandQueue> mCommandQueue;
};

} /* namespace sfml_playground */
