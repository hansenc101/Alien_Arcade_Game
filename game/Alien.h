#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Alien
{
private:
	Sprite alien;
	Texture alienTexture;
	int ID;
public:
	Alien();
	Alien(Vector2f, int);
	void setID(int);
	int getID();
	void setPosition(Vector2f);
	Vector2f getPosition();
	void moveAlien(int, int);
	Sprite getSprite();
};
