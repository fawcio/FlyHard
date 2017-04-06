/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Sławomir Cielepak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "World.hpp"
#include <random>
#include <cmath>

#include "entities/Stars.hpp"
#include "entities/PlayerAircraft.hpp"
#include "utils/TypesAndTools.hpp"
#include "commands/CommandCategory.hpp"
#include "commands/CommandQueue.hpp"

namespace SFGame
{

const uint32_t World::cFrameLimit = 120000;
const sf::Time World::cTimePerFrame = sf::milliseconds(10);

const float World::cMinScrollSpeed = -15.f;
const float World::cMaxScrollSpeed = -100.f;

World::World(sf::RenderWindow& window) :
    mWindow(window),
    mWorldView(window.getDefaultView()),
    mWorldBoudns(0.0f, 0.0f, mWorldView.getSize().x, 100000.0f),
    mSpawnPosition(mWorldView.getSize().x / 2.0f, mWorldBoudns.height - 100.0f),
    mPlayerAircraft(nullptr),
    mCommandQueue(new CommandQueue {})
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
    while (!mCommandQueue->isEmpty())
    {
        mScenGraph.onCommand(mCommandQueue->pop());
    }

    mWorldView.setCenter(mWindow.getSize().x/2.f, mPlayerAircraft->getPosition().y-300);

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

    mSceneLayers[LayerID::eFarGalaxy]->attachChild(std::make_unique<Stars>(mWorldBoudns, 100000, [this](float& upperBound, float& lowerBound) {
        lowerBound = mPlayerAircraft->getPosition().y-700;
        upperBound = mPlayerAircraft->getPosition().y+100;
    }));

    auto playerAircraft = std::make_unique<PlayerAircraft>(mSpawnPosition, 0.f, mTextures, *this);
    mPlayerAircraft = playerAircraft.get();

    mSceneLayers[LayerID::eAir]->attachChild(std::move(playerAircraft));
}

} /* namespace sfml_playground */
