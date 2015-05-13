/*
 * Category.hpp
 *
 *  Created on: 13 maj 2015
 *      Author: slawek
 */

#ifndef UTILS_CATEGORY_HPP_
#define UTILS_CATEGORY_HPP_

namespace sfml_playground
{

enum class Category : int
{
	None			= 0,
	Scene			= 1,
	PlayerAircraft	= 1 << 1,
	EnemyAircraft	= 1 << 2
};

}

#endif /* UTILS_CATEGORY_HPP_ */
