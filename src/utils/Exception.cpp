/*
 * Exception.cpp
 *
 *  Created on: 11 lis 2014
 *      Author: slawek
 */

#include "Exception.hpp"

namespace sfml_playground
{

Exception::Exception(const sf::String& cause)
{
	mCause = cause;
}

Exception::~Exception()
{
}

} /* namespace sfml_playground */
