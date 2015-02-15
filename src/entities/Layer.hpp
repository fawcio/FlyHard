/*
 * Layer.hpp
 *
 *  Created on: 15 lut 2015
 *      Author: slawek
 */

#ifndef ENTITIES_LAYER_HPP_
#define ENTITIES_LAYER_HPP_

#include "SceneNode.hpp"

namespace sfml_playground
{

class Layer: public SceneNode
{
public:
	enum class LayerID
	{
		eBackground,
		eAir,
		eLayerCount
	};

public:
	Layer();
	virtual ~Layer();
};

}

#endif /* ENTITIES_LAYER_HPP_ */
