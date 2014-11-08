/*
 * Player.h
 *
 *  Created on: 6 lis 2014
 *      Author: slawek
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <SFML/Graphics.hpp>
#include "IDrawable.hpp"

namespace sfml_playground
{

class Player : public IDrawable
{
public:
	Player();
	virtual ~Player();

	void setMovingUp(bool isMoving);

	void setMovingDown(bool isMoving);

	void setMovingLeft(bool isMoving);

	void setMovingRight(bool isMoving);

	virtual void setWindow(sf::RenderWindow* window);

	virtual void draw() override;

	void update();

private:

	sf::RenderWindow*	mWindow;
	sf::Sprite			mSprite;
	sf::Texture			mTexture;

	bool isMovingUp;
	bool isMovingDown;
	bool isMovingLeft;
	bool isMovingRight;

	const float cSpeed = 0.2f; //(200 pix/s)
};

} /* namespace sfml_playground */

#endif /* PLAYER_HPP_ */
