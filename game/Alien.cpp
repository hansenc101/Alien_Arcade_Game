#include "Alien.h"
#include <iostream>
using namespace std;

Alien::Alien()
{
	if (!alienTexture.loadFromFile("alien.png"))
	{
		cout << "Unable to load alien texture!" << endl;
		exit(EXIT_FAILURE);
	}
	alien.setTexture(alienTexture);
	ID = 0;
}

Alien::Alien(Vector2f pos, int num)
{
	if (!alienTexture.loadFromFile("alien.png"))
	{
		cout << "Unable to load alien texture!" << endl;
		exit(EXIT_FAILURE);
	}
	alien.setTexture(alienTexture);
	alien.setScale(1.5, 1.5);
	alien.setPosition(pos);
	ID = num;
}

void Alien::setID(int num)
{
	ID = num;
}

int Alien::getID()
{
	return ID;
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