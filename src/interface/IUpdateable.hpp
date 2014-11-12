/*
 * IUpdateable.hpp
 *
 *  Created on: 11 lis 2014
 *      Author: slawek
 */

#ifndef IUPDATEABLE_HPP_
#define IUPDATEABLE_HPP_

namespace sfml_playground
{

class IUpdateable
{
public:
	virtual ~IUpdateable() {}

	virtual void update() = 0;
};

} /* namespace sfml_playground */

#endif /* IUPDATEABLE_HPP_ */
