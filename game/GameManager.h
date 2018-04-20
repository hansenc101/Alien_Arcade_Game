#pragma once
#include <iostream>
#include "Ship.h"
#include "Alien.h"
#include "Projectile.h"
#include <list>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class GameManager
{
private:
	int level;
	int numLivesLeft;
	int numAliensLeft;
	int kills;
	list<Missile> missiles;
	list<Bomb> bombs;
	list<Alien> aliens;
public:
	GameManager();
	void setLevel(Texture*);

	int getLevel()
	{  return level;  }

	void subtractLife()
	{ 
		numLivesLeft--;
		cout << "Life Lost! ---- Lives left: " << numLivesLeft << endl;
	}

	int getLives()
	{  return numLivesLeft;  }

	void subtractAlien()
	{  
		numAliensLeft--; 
	}

	int getNumAliensLeft()
	{  return numAliensLeft;  }

	void setupAliens(Texture*);
	void launchMissile(Vector2f, Texture*);
	void bombsAway(int, Texture*);
	void moveProjectiles(RenderWindow&);
	void moveAliens(RenderWindow&);
	void checkAliensAndMissiles();
	bool isShipHit(Sprite&);
	void displayStats(RenderWindow&);
	bool start(RenderWindow&, Event&);
	void end(RenderWindow&, int);
};