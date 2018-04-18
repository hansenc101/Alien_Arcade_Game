#include "Missile.h"
#include <iostream>
using namespace std;

const int DISTANCE = 5;

Missile::Missile()
{
	if (!missileTexture.loadFromFile("missile.png"))
	{
		cout << "Unable to load missile texture!" << endl;
		exit(EXIT_FAILURE);
	}
	missile.setTexture(missileTexture);
	missile.setScale(1.5, 1.5);
}

Missile::Missile(Vector2f pos)
{
	if (!missileTexture.loadFromFile("missile.png"))
	{
		cout << "Unable to load missile texture!" << endl;
		exit(EXIT_FAILURE);
	}
	missile.setTexture(missileTexture);
	missile.setScale(1.5, 1.5);
	missile.setPosition(pos);
}

void Missile::setPosition(Vector2f pos)
{
	missile.setPosition(pos);
}

Vector2f Missile::getPosition()
{
	return missile.getPosition();
}

void Missile::moveMissile()
{
	missile.move(0, -2 * DISTANCE);
}