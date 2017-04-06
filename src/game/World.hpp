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
#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "resource_mgmt/ResourceHolder.hpp"
#include "entities/SceneNode.hpp"
#include "utils/Units.hpp"
#include "utils/NonCopyable.hpp"

namespace SFGame
{

/**
 * Forward declarations
 */
class CommandQueue;
class SceneNode;

class World : NonCopyable
{
public:
    explicit	World(sf::RenderWindow& window);
	virtual			~World();

    void		update();
    void 		draw();

	std::weak_ptr<CommandQueue> getCommandQueue() const { return mCommandQueue; }

    const sf::FloatRect& getWorldBounds() const { return mWorldBoudns; }

private:
    void		loadTextures();
    void		buildScene();

private:
	enum LayerID : std::size_t
	{
        eFarGalaxy,
		eAir,
		eForeground,

		eLayerCount
	};

public:

    static const uint32_t	cFrameLimit;
	static const sf::Time	cTimePerFrame;
    static float    		ScrollSpeed;
    static const float      cMaxScrollSpeed;
    static const float      cMinScrollSpeed;

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
