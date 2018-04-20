#pragma once
#include "Projectile.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Alien
{
private:
	Sprite alien;
	int ID;
public:
	Alien(Vector2f, Texture*, int);
	void setPosition(Vector2f);
	Vector2f getPosition();
	void moveAlien(int, int);
	Sprite getSprite();
	void dropBomb();
};
