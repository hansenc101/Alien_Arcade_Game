#include "GameManager.h"
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

GameManager::GameManager()
{
	level = 1;
	numLivesLeft = 3;
	numAliensLeft = 10;
	kills = 0;
}

void GameManager::setLevel(Texture* alienTexture)
{
	if (numAliensLeft == 0)
	{
		level++;
		setupAliens(alienTexture);
	}
}

void GameManager::setupAliens(Texture* alienTexture)
{
	aliens.clear();
	numAliensLeft = 10;
	for (int i = 0; i < 10; i++)
	{
		Vector2f pos;
		pos.x = 20 + (75 * i);
		Alien tempAlien(pos, alienTexture, (i + 1));
		aliens.push_back(tempAlien);
	}
}

void GameManager::launchMissile(Vector2f pos, Texture* missileTexture)
{
	Missile tempMissile(pos, missileTexture);
	missiles.push_back(tempMissile);
}

void GameManager::bombsAway(int alienNum, Texture * bombTexture)
{
	int i = 0;
	list<Alien>::iterator alienIter;
	alienIter = aliens.begin();
	Vector2f pos;
	while (i <= alienNum && alienIter != aliens.end())
	{
		if (i == alienNum)
		{
			pos = alienIter->getPosition();
			Bomb tempBomb(pos, bombTexture);
			bombs.push_back(tempBomb);
		}
		alienIter++;
		i++;
	}
}

void GameManager::moveProjectiles(RenderWindow &window)
{
	list<Missile>::iterator missileIter;
	for (missileIter = missiles.begin(); missileIter != missiles.end(); missileIter++)
	{
		window.draw(missileIter->getSprite());
		missileIter->move();
	}
	list<Bomb>::iterator bombIter;
	for (bombIter = bombs.begin(); bombIter != bombs.end(); bombIter++)
	{
		window.draw(bombIter->getSprite());
		bombIter->move();
	}
}

void GameManager::moveAliens(RenderWindow &window)
{
	list<Alien>::iterator alienIter;
	for (alienIter = aliens.begin(); alienIter != aliens.end(); alienIter++)
	{
		window.draw(alienIter->getSprite());
		alienIter->moveAlien(0, 1);
	}
}

void GameManager::checkAliensAndMissiles()
{
	list<Alien>::iterator alienIter;
	list<Missile>::iterator missileIter;
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
				kills++;
			}
			else
				missileIter++;
		}
		if (hit)
		{
			alienIter = aliens.erase(alienIter);
			subtractAlien();
		}
		else if (alienIter->getPosition().y >= WINDOW_HEIGHT - 40)
		{
			alienIter = aliens.erase(alienIter);
			subtractAlien();
		}
		else
			alienIter++;
	}
}

bool GameManager::isShipHit(Sprite &ship)
{
	bool isHit = false;
	list<Bomb>::iterator bombIter;
	list<Alien>::iterator alienIter;
	FloatRect shipBounds = ship.getGlobalBounds();
	for (bombIter = bombs.begin(); bombIter != bombs.end();)
	{
		FloatRect bombBounds = bombIter->getSprite().getGlobalBounds();
		if (shipBounds.intersects(bombBounds))
		{
			bombIter = bombs.erase(bombIter);
			subtractLife();
			missiles.clear();
			isHit = true;
		}
		else
		{
			bombIter++;
		}
	}
	alienIter = aliens.begin();
	while (alienIter != aliens.end() && !isHit)
	{
		FloatRect alienBounds = alienIter->getSprite().getGlobalBounds();
		if (shipBounds.intersects(alienBounds) || (alienIter->getPosition().y + 50) >= WINDOW_HEIGHT)
		{
			isHit = true;
			missiles.clear();
			subtractLife();
		}
		alienIter++;
	}

	return isHit;
}

void GameManager::displayStats(RenderWindow &window)
{
	Font font;
	string livesLeftString = to_string(numLivesLeft);
	string killsString = to_string(kills);
	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		exit(EXIT_FAILURE);
	Text livesLeft("Lives Left: " + livesLeftString, font, 20);
	livesLeft.setPosition(20, 20);
	Text kills("Kills: " + killsString, font, 20);
	kills.setPosition(20, 60);
	window.draw(livesLeft);
	window.draw(kills);
}

bool GameManager::start(RenderWindow &window, Event &event)
{
	Font font;
	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		exit(EXIT_FAILURE);
	Text start("START", font, 50);
	start.setPosition(WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 2 - 50);
	Text level("Level: " + to_string(level), font, 50);
	level.setPosition(WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 2);
	bool ready = false;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == Event::Closed)
			window.close();
		else if (event.type == Event::MouseButtonReleased)
		{
			ready = true;
		}
	}
	window.draw(start);
	window.draw(level);
	window.display();
	return ready;
}

void GameManager::end(RenderWindow &window, int winner)
{
	Font font;
	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		exit(EXIT_FAILURE);

	if (winner == 0)
	{
		Text end("CONGRADULATIONS, YOU WON!", font, 50);
		end.setPosition(10, WINDOW_HEIGHT / 2 - 150);
		window.draw(end);
		window.display();
		level = 1;
		numLivesLeft = 3;
	}
	else
	{
		Text end("YOU LOST. TOO BAD.", font, 50);
		end.setPosition(150, WINDOW_HEIGHT / 2 - 150);
		window.draw(end);
		window.display();
		level = 1;
		numLivesLeft = 3;
		kills = 0;
	}
}
