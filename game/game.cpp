#include <iostream>
#include <list>
#include "GameManager.h"
#include "Alien.h"
#include "Ship.h"
#include "Projectile.h"
#include <cstdlib>
#include <ctime>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf; 

//============================================================
// Christopher Hansen
// Assignment 08
// 4/16/2018
// Known Bugs: N/A
//============================================================

// note: a Sprite represents an image on screen. A sprite knows and remembers its own position
// ship.move(offsetX, offsetY) adds offsetX, offsetY to 
// the current position of the ship. 
// x is horizontal, y is vertical. 
// 0,0 is in the UPPER LEFT of the screen, y increases DOWN the screen

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);
	GameManager game; // basically controls the whole game
	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.
	Texture starsTexture; // texture for background
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture alienTexture; // texture for alien sprite
	if (!alienTexture.loadFromFile("enemy.png"))
	{
		cout << "Unable to load alien texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture alienTexture2; // texture for level 2 aliens
	if (!alienTexture2.loadFromFile("enemy2.png"))
	{
		cout << "Unable to load alien texture!" << endl;
		exit(EXIT_FAILURE);
	}

	Texture missileTexture; // texture for missile sprite
	if (!missileTexture.loadFromFile("missile.png"))
	{
		cout << "Unable to load missile texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture bombTexture; // texture for bomb sprite
	if (!bombTexture.loadFromFile("laser.png"))
	{
		cout << "Unable to load bomb texture!" << endl;
		exit(EXIT_FAILURE);
	}

	Sprite background;
	background.setTexture(starsTexture);
	// The texture file is 640x480, so scale it up a little to cover 800x600 window
	background.setScale(1.5, 1.5);
	game.setupAliens(&alienTexture);

	// initial position of the ship will be approx middle/bottom of screen
	Ship ship; // ship instance
	float shipX = window.getSize().x - 50; // initial x position of ship
	float shipY = window.getSize().y - 50; // initial y position of ship
	ship.setPosition(shipX, shipY);

	int counter = 0; // keep track of how many frames have passed
	int maxValue = 10; // max number of aliens, used to decide which one will drop a bomb
	int minValue = 1; // min number of aliens, used to decide which one will drop a bomb
	int choice = 0; // first choice to determine which alien will drop a bomb
	int choice2 = 0; // second choice to determine which alien will drop a bomb
	unsigned seed = time(0); // get the system time
	srand(seed); 
	bool ready = false; // used to test to see if the player is ready or not

	while (window.isOpen())
	{
		Event event;
		counter++;
		if (game.getLevel() == 1)
		{
			if (counter % 90 == 0)
			{
				choice = (rand() % (maxValue - minValue + 1)) + minValue;
				choice2 = (rand() % (maxValue - minValue + 1)) + minValue;
				game.bombsAway(choice, &bombTexture);
				game.bombsAway(choice2, &bombTexture);
				counter = 0;
			}
		}
		else if (game.getLevel() == 2)
		{
			if (counter % 60 == 0)
			{
				choice = (rand() % (maxValue - minValue + 1)) + minValue;
				choice2 = (rand() % (maxValue - minValue + 1)) + minValue;
				game.bombsAway(choice, &bombTexture);
				game.bombsAway(choice2, &bombTexture);
				counter = 0;
			}
		}
		
		// draw background first, so everything that's drawn later 
		// will appear on top of background
		window.draw(background);
		// check all the window's events that were triggered since the last iteration of the loop
		// For now, we just need this so we can click on the window and close it
		

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					// handle space bar
					game.launchMissile(ship.getPosition(), &missileTexture);
				}
				
			}
		}

		while (!ready)
		{
			if (game.getLevel() < 3 && game.getLives() > 0)
			{
				ready = game.start(window, event);
			}
			else if (game.getLevel() >= 3 && game.getLives() > 0)
			{
				game.end(window, 0);
				ready = game.start(window, event);
			}
			else if (game.getLives() <= 0)
			{
				ready = game.start(window, event);
				game.end(window, 1);
			}
		}

		ship.moveShip();
		window.draw(ship.getSprite());

		// moving our missiles we launched
		game.moveProjectiles(window);
		// Testing to see if our ship is hit
		Sprite shipSprite = ship.getSprite();
		bool hit = game.isShipHit(shipSprite);
		if (hit)
		{
			if(game.getLevel() == 1)
				game.setupAliens(&alienTexture);
			else
				game.setupAliens(&alienTexture2);
		}

		// moving aliens
		game.moveAliens(window);
		// testing to see if any of our aliens were hit with any of our missiles
		game.checkAliensAndMissiles();

		game.displayStats(window);
		// end the current frame; this makes everything that we have 
		// already "drawn" actually show up on the screen
		if (game.getNumAliensLeft() == 0)
		{
			if (game.getLevel() == 1)
				game.setLevel(&alienTexture2);
			else
				game.setLevel(&alienTexture);
			ready = false;
			window.clear();
		} else if (game.getLives() <= 0)
		{
			game.setLevel(&alienTexture);
			ready = false;
			window.clear();
		}

		window.display();

		// At this point the frame we have built is now visible on screen.
		// Now control will go back to the top of the animation loop
		// to build the next frame. Since we begin by drawing the
		// background, each frame is rebuilt from scratch.

	} // end body of animation loop

	return 0;
}

