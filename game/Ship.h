#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Ship
{
private:
	Sprite ship;
	Texture shipTexture;
public:
	Ship();
	void setPosition(int, int);
	Vector2f getPosition();
	void moveShip();
	Sprite getSprite()
	{
		return ship;
	}
};