/*
 * Exception.h
 *
 *  Created on: 11 lis 2014
 *      Author: slawek
 */

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>
#include <SFML/Graphics.hpp>

namespace sfml_playground
{

class Exception: public std::exception
{
public:
	Exception(const sf::String& cause);
	virtual ~Exception();

	sf::String getCause() { return mCause; }

private:

	sf::String mCause;
};

} /* namespace sfml_playground */

#endif /* EXCEPTION_HPP_ */
