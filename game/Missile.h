#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Missile
{
private:
	Sprite missile;
	Texture missileTexture;
public:
	Missile();
	Missile(Vector2f);
	void setPosition(Vector2f);
	Vector2f getPosition();
	void moveMissile();
	Sprite getSprite()
	{
		return missile;
	}
};