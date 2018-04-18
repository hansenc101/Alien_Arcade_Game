#include <iostream>
#include <list>
#include "GameManager.h"
#include "Alien.h"
#include "Ship.h"
#include "Missile.h"
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

	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.
	
	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}
	
	list<Missile> missiles;
	list<Missile>::iterator missileIter;

	list<Alien> aliens;
	list<Alien>::iterator alienIter;
	for (int i = 0; i < 10; i++)
	{
		Vector2f pos;
		pos.x = 20 + (75 * i );
		Alien tempAlien(pos, i);
		aliens.push_back(tempAlien);
	}


	Sprite background;
	background.setTexture(starsTexture);
	// The texture file is 640x480, so scale it up a little to cover 800x600 window
	background.setScale(1.5, 1.5);

	// create sprite and texture it
	


	// initial position of the ship will be approx middle of screen
	Ship ship;
	float shipX = window.getSize().x - 50;
	float shipY = window.getSize().y - 50;
	ship.setPosition(shipX, shipY);

	GameManager game;


	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		// For now, we just need this so we can click on the window and close it
		Event event;

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
					Missile tempMissile(ship.getPosition());
					tempMissile.setPosition(ship.getPosition());
					missiles.push_back(tempMissile);
				}
				
			}
		}

		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		// draw background first, so everything that's drawn later 
		// will appear on top of background
		window.draw(background);

		ship.moveShip();

		// draw the ship on top of background 
		// (the ship from previous frame was erased when we drew background)
		window.draw(ship.getSprite());

		// moving our missiles we launched
		for (missileIter = missiles.begin(); missileIter != missiles.end() ; missileIter++)
		{
			window.draw(missileIter->getSprite());
			missileIter->moveMissile();
		}

		// moving our missiles we launched
		for (alienIter = aliens.begin(); alienIter != aliens.end(); alienIter++)
		{
			window.draw(alienIter->getSprite());
			alienIter->moveAlien(0, 1);
		}

		// testing to see if any of our aliens were hit with any of our missiles
		for (alienIter = aliens.begin(); alienIter != aliens.end();)
		{
			bool hit = false;
			FloatRect alienBounds = alienIter->getSprite().getGlobalBounds();
			for (missileIter = missiles.begin(); missileIter != missiles.end();)
			{
				FloatRect missileBounds = missileIter->getSprite().getGlobalBounds();
				if (missileBounds.intersects(alienBounds))
				{
					missileIter = missiles.erase(missileIter);
					hit = true;
				}
				else
					missileIter++;
			}
			if (hit)
			{
				alienIter = aliens.erase(alienIter);
				game.subtractAlien();
			}
			else
				alienIter++;
		}




		// end the current frame; this makes everything that we have 
		// already "drawn" actually show up on the screen
		window.display();

		// At this point the frame we have built is now visible on screen.
		// Now control will go back to the top of the animation loop
		// to build the next frame. Since we begin by drawing the
		// background, each frame is rebuilt from scratch.

	} // end body of animation loop

	return 0;
}

