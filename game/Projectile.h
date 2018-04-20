#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

const int DISTANCE = 5;

class Projectile
{
private:
	Sprite projectile;
public:
	virtual void move()
	{
	}
	virtual Sprite getSprite()
	{
		return projectile;
	}
};

class Missile : public Projectile
{
private:
	Sprite missile;
public:
	Missile(Vector2f pos, Texture* missileTexture)
	{
		missile.setTexture(*missileTexture);
		missile.setScale(1.5, 1.5);
		missile.setPosition(pos);
	}
	void move()
	{  missile.move(0, -2 * DISTANCE);  }

	Sprite getSprite()
	{  return missile;  }
};

class Bomb : public Projectile
{
private:
	Sprite bomb;
public:
	Bomb(Vector2f pos, Texture* bombTexture)
	{
		bomb.setTexture(*bombTexture);
		bomb.setScale(1.5, 1.5);
		bomb.setPosition(pos.x + 15, pos.y);
	}
	void move()
	{
		bomb.move(0,2 + DISTANCE);
	}

	Sprite getSprite()
	{
		return bomb;
	}
};
