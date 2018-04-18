#pragma once
class GameManager
{
private:
	int level;
	int numLivesLeft;
	int numAliensLeft;
public:
	GameManager()
	{
		level = 1;
		numLivesLeft = 3;
		numAliensLeft = 10;
	}

	void setLevel(int newLevel)
	{
		level = newLevel;
	}

	int getLevel()
	{
		return level;
	}

	void subtractLife()
	{
		numLivesLeft--;
	}

	int getLives()
	{
		return numLivesLeft;
	}

	void subtractAlien()
	{
		numAliensLeft--;
	}

	int getNumAliensLeft()
	{
		return numAliensLeft;
	}
};