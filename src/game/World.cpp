/*
 * World.cpp
 *
 *  Created on: 16 lut 2015
 *      Author: slawek
 */

#include <cassert>
#include "World.hpp"
#include "SpriteNode.hpp"

namespace sfml_playground
{

const sf::Time World::cTimePerFrame = sf::milliseconds(2);

World::World(sf::RenderWindow& window) :
		mWindow(window),
		mWorldView(window.getDefaultView()),
		mWorldBoudns(0.0f, 0.0f, mWorldView.getSize().x, 100000.0f),
		mSpawnPosition(mWorldView.getSize().x / 2.0f, mWorldBoudns.height - 100.0f),
		mScrollSpeed(-400.0f),
		mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mWorldBoudns.width / 2.0f, mWorldBoudns.height - mWindow.getSize().y / 2.0f);
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
	mTextures.load(TextureID::eRaptor_shadow, "Resources/images/Raptor_shadow.png");
	mTextures.load(TextureID::eLandscape, "Resources/images/Sand-Background_blurred.png");
}

void World::buildScene()
{
	// Add layers to scene graph
	for (std::size_t i=0; i < LayerID::eLayerCount; ++i)
	{
		std::unique_ptr<SceneNode> layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mScenGraph.attachChild(std::move(layer));
	}

	sf::Texture& texture = mTextures.get(TextureID::eLandscape);
	sf::IntRect  textureRect(mWorldBoudns);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBoudns.left, mWorldBoudns.top);
	mSceneLayers[LayerID::eBackground]->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Entity> playerAircraft(new Entity());
	playerAircraft->setPosition(mSpawnPosition);

	std::unique_ptr<Aircraft> raptor(new Aircraft(TextureID::eRaptor, mTextures));
	std::unique_ptr<Aircraft> raptor_shadow(new Aircraft(TextureID::eRaptor_shadow, mTextures));
	raptor_shadow->setPosition(-40.0f, 60.0f);
	raptor->setVelocity(0.0f, mScrollSpeed);
	raptor_shadow->setVelocity(0.0f, mScrollSpeed);
	mPlayerAircraft = playerAircraft.get();

	playerAircraft->attachChild(std::move(raptor_shadow));
	playerAircraft->attachChild(std::move(raptor));

	mSceneLayers[LayerID::eAir]->attachChild(std::move(playerAircraft));


}

} /* namespace sfml_playground */
