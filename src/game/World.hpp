#ifndef GAME_WORLD_HPP_
#define GAME_WORLD_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "resource_mgmt/ResourceHolder.hpp"
#include "entities/SceneNode.hpp"
#include "commands/CommandQueue.hpp"

namespace sfml_playground
{

class World: private sf::NonCopyable
{
public:
    explicit		World(sf::RenderWindow& window);
	virtual			~World();

	void			update();
	void 			draw();

    std::shared_ptr<CommandQueue> getCommandQueue() const { return mCommandQueue; }

    const sf::FloatRect& getWorldBounds() const { return mWorldBoudns; }
    float getScrollSpeed() const { return mScrollSpeed; }

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
	sf::RenderWindow&		mWindow;
	sf::View				mWorldView;
	TextureHolder			mTextures;
	SceneNode				mScenGraph;
	std::array<SceneNode*, LayerID::eLayerCount> mSceneLayers;

	sf::FloatRect			mWorldBoudns;
	sf::Vector2f			mSpawnPosition;
	float					mScrollSpeed;
	SceneNode*				mPlayerAircraft;

	std::shared_ptr<CommandQueue> mCommandQueue;
};

} /* namespace sfml_playground */

#endif /* GAME_WORLD_HPP_ */
