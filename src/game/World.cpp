/*
 * World.cpp
 *
 *  Created on: 16 lut 2015
 *      Author: slawek
 */

#include <cassert>
#include "World.hpp"
#include "SpriteNode.hpp"
#include "FPS.hpp"

namespace sfml_playground
{

const sf::Time World::cTimePerFrame = sf::milliseconds(2);

World::World(sf::RenderWindow& window) :
		mWindow(window),
		mWorldView(window.getDefaultView()),
		mWorldBoudns(0.0f, 0.0f, mWorldView.getSize().x, 100000.0f),
		mSpawnPosition(mWorldView.getSize().x / 2.0f, mWorldBoudns.height - mWorldView.getSize().y),
		mScrollSpeed(-400.0f),
		mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition - sf::Vector2f(0.0f, 300.0f));
}

World::~World()
{
}

void World::update()
{
	mWorldView.move(0.0f, mScrollSpeed * cTimePerFrame.asSeconds());

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
	// Add layers to scene graph
	for (std::size_t i=0; i < LayerID::eLayerCount; ++i)
	{
		SceneNode::SceneNodePtr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mScenGraph.attachChild(std::move(layer));
	}

	sf::Texture& texture = mTextures.get(TextureID::eLandscape);
	sf::IntRect  textureRect(mWorldBoudns);
	texture.setRepeated(true);

	std::unique_ptr<FPS> fpsMeter(new FPS());
	mSceneLayers[LayerID::eForeground]
				 ->attachChild(std::move(fpsMeter));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBoudns.left, mWorldBoudns.top);
	mSceneLayers[LayerID::eBackground]
	             ->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Type::eRaptor, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(0.0f, mScrollSpeed);
	mSceneLayers[LayerID::eAir]
	             ->attachChild(std::move(leader));
}

} /* namespace sfml_playground */
