/*
 * World.cpp
 *
 *  Created on: 16 lut 2015
 *      Author: slawek
 */

#include "World.hpp"
#include "SpriteNode.hpp"

namespace sfml_playground
{

const sf::Time World::cTimePerFrame = sf::milliseconds(2);

World::World(sf::RenderWindow& window) :
		mWindow(window),
		mWorldView(window.getDefaultView()),
		mWorldBoudns(0.0f, 0.0f, mWorldView.getSize().x, 2000.0f),
		mSpawnPosition(mWorldView.getSize().x / 2.0f, mWorldBoudns.height - mWorldView.getSize().y),
				mPlayerAircraft(nullptr),
		mScrollSpeed(0.1f)
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

World::~World()
{
	// TODO Auto-generated destructor stub
}

void World::update()
{
	mWorldView.move(0.0f, mScrollSpeed * cTimePerFrame.asSeconds());

	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	if (position.x <= mWorldBoudns.left + 150 || position.x >= mWorldBoudns.left + mWorldBoudns.width - 150)
	{
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}

	mScenGraph.update();
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mScenGraph);
}

void World::loadTextures()
{
	mTextures.load(TextureID::eRaptor, "Resources/images/Raptor.png");
	mTextures.load(TextureID::eEagle, "Resources/images/Raptor.png");
	mTextures.load(TextureID::eLandscape, "Resources/images/Sand-Background.png");
}

void World::buildScene()
{
	for (std::size_t i=0; i < cLayerCount; ++i)
	{
		SceneNode::SceneNodePtr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mScenGraph.attachChild(std::move(layer));
	}

	sf::Texture& texture = mTextures.get(TextureID::eLandscape);
	sf::IntRect  textureRect(mWorldBoudns);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBoudns.left, mWorldBoudns.top);
	mSceneLayers[static_cast<std::size_t>(LayerID::eBackground)]
	             ->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Type::eRaptor, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.0f, mScrollSpeed);
	mSceneLayers[static_cast<std::size_t>(LayerID::eAir)]
	             ->attachChild(std::move(leader));
}

} /* namespace sfml_playground */
