#include "Alien.h"
#include <iostream>
using namespace std;

Alien::Alien(Vector2f pos,Texture* alienTexture, int id)
{
	alien.setTexture(*alienTexture);
	alien.setPosition(pos);
	ID = id;
}

void Alien::setPosition(Vector2f pos)
{
	alien.setPosition(pos);
}

Vector2f Alien::getPosition()
{
	return alien.getPosition();
}

void Alien::moveAlien(const int x, const int y)
{
	alien.move(x, y);
}

Sprite Alien::getSprite()
{
	return alien;
}

void Alien::dropBomb()
{

}