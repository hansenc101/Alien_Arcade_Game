#include "Ship.h"
#include <iostream>
using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Ship::Ship()
{
	if (!shipTexture.loadFromFile("ship.png"))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}
	ship.setTexture(shipTexture);
	ship.setScale(2.0, 2.0);
}

void Ship::setPosition(int x, int y)
{
	ship.setPosition(x, y);
}

Vector2f Ship::getPosition()
{
	return ship.getPosition();
}

void Ship::moveShip()
{
	const float DISTANCE = 5.0;

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		// left arrow is pressed: move our ship left 5 pixels
		// 2nd parm is y direction. We don't want to move up/down, so it's zero.
		if (ship.getPosition().x >= 0)
			ship.move(-DISTANCE, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		// right arrow is pressed: move our ship right 5 pixels
		if (ship.getPosition().x + ship.getGlobalBounds().width <= WINDOW_WIDTH)
			ship.move(DISTANCE, 0);
	}
}