/*
 * Aircraft.hpp
 *
 *  Created on: 5 sty 2015
 *      Author: slawek
 */

#ifndef ENTITIES_AIRCRAFT_HPP_
#define ENTITIES_AIRCRAFT_HPP_

#include <Entity.hpp>

namespace sfml_playground
{

class Aircraft: public Entity
{
public:
	enum class Type
	{
		Eagle,
		Raptor
	};

	explicit Aircraft(Type type) { mType = type; }

private:
	Type	mType;
};

} /* namespace sfml_playground */

#endif /* ENTITIES_AIRCRAFT_HPP_ */
