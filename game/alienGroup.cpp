#include "alienGroup.h"
#include "shotMgr.h"
#include <iostream>
#include <ctime>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

alienGroupMgr::alienGroupMgr()
{
	
	if (!alienEasyTexture.loadFromFile("alien.png"))
	{
		cout << "Unable to load alien (1) texture!" << endl;
		exit(EXIT_FAILURE);
	}

	if (!alienHardLvlTexture.loadFromFile("alien2.png"))
	{
		cout << "Unable to load alien (2) texture!" << endl;
		exit(EXIT_FAILURE);
	}

}

void alienGroupMgr::draw(RenderWindow & win)
{
	for (list<alien*>::iterator iter = theGang.begin(); iter != theGang.end(); iter++)
	{
		alien* ptrShot = *iter;
		ptrShot->draw(win);
	}
}

void alienGroupMgr::sideMove(bool time)
{
	int count = 0;

	for (list<alien*>::iterator iter = theGang.begin(); iter != theGang.end(); iter++)
	{
		alien* ptrShot = *iter;
		float pos = ptrShot->getSprite().getPosition().x;

		float DISTANCE;

		if (ptrShot->getType() == LEVEL_ONE_EASY || ptrShot->getType() == LEVEL_TWO_EASY)
			DISTANCE = 0.5f;
		else if (ptrShot->getType() == LEVEL_ONE_HARD || ptrShot->getType() == LEVEL_TWO_HARD)
			DISTANCE = 1.0f;

		if (wallSwitch)
		{
			if (time)
			{
				if (count % 2 * count == 0)
					ptrShot->getSprite().move(DISTANCE, -DISTANCE);
				else
					ptrShot->getSprite().move(DISTANCE, DISTANCE);
			}
			else
			{
				if (count % 2 == 0)
					ptrShot->getSprite().move(DISTANCE, DISTANCE);
				else
					ptrShot->getSprite().move(DISTANCE, -DISTANCE);
			}
		}
		else
		{
			if (time)
			{
				if (count % 2 == 0)
					ptrShot->getSprite().move(-DISTANCE, -DISTANCE);
				else
					ptrShot->getSprite().move(-DISTANCE, DISTANCE);
			}
			else
			{
				if (count % 2 == 0)
					ptrShot->getSprite().move(-DISTANCE, DISTANCE);
				else
					ptrShot->getSprite().move(-DISTANCE, -DISTANCE);
			}
		}
		
		if (pos < 0)
		{
			wallSwitch = true;
			downMove();

		}
		else if (pos > 778)
		{
			wallSwitch = false;
			downMove();
		}

		count++;
	}
}

void alienGroupMgr::downMove()
{
	for (list<alien*>::iterator iter = theGang.begin(); iter != theGang.end(); iter++)
	{
		alien* ptrShot = *iter;
		float DISTANCE = 3.5f;

		ptrShot->getSprite().move(0, DISTANCE);
	}
}

int alienGroupMgr::disappear(shotMgr m, bool & hit)
{
	int bulletIndex = -1;

	for (list<alien*>::iterator iter = theGang.begin(); iter != theGang.end() && !hit;)
	{
		alien* ptrShot = *iter;
		FloatRect alienBound = ptrShot->getSprite().getGlobalBounds();

		for (int i = 0; i < m.getAmountFilled() && !hit; i++)
		{
			FloatRect bulletBound = m.getList(i)->getSprite().getGlobalBounds();

			if (alienBound.intersects(bulletBound) && m.getList(i)->getType() == MISSILE || ptrShot->getSprite().getPosition().y >= 600)
			{
				hit = true;
				bulletIndex = i;
			}
		}

		if (hit)
		{
			iter = theGang.erase(iter);
		}
		else
		{
			iter++;
		}

	}

	return bulletIndex;

}

void alienGroupMgr::RandomBombDrop(shotMgr& m)
{
		Vector2f loc;
		bool found = false;

		unsigned seed = time(0);
		srand(seed);

		const int MIN_VALUE = 0;
		const int MAX_VALUE = theGang.size();

		int value = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;
		int count = 0;
	

		for (list<alien*>::iterator iter = theGang.begin(); !found && iter != theGang.end(); iter++)
		{

			if (value == count)
			{
				loc = (*iter)->getSprite().getPosition();
				found = true;
			}

			count++;
		}
		if (found)
		{
			m.shoot(BOMB, loc);
		}
	
}

alien * alienGroupMgr::getlist(int i)
{
	int count = 0;
	for (list<alien*>::iterator iter = theGang.begin(); iter != theGang.end();)
	{
		if (count == i)
			return *iter;

		else
			iter++;

		count++;
	}
}

void alienGroupMgr::reset()
{
	for (list<alien*>::iterator iter = theGang.begin(); iter != theGang.end();)
	{
			iter = theGang.erase(iter);
	}
	

	if (lvl == LEVEL_ONE_EASY)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				Vector2f vec(135 + (90 * j), 50 + (70 * i));
				theGang.push_back(new lvlOne_Easy(vec, alienEasyTexture));
			}
		}
	}

	else if (lvl == LEVEL_TWO_HARD)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				Vector2f vec(135 + (90 * j), 50 + (70 * i));
				theGang.push_back(new lvlOne_Hard(vec, alienHardLvlTexture));
			}
		}
	}

	else if (lvl == LEVEL_ONE_HARD)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 8;)
			{
				Vector2f vec(135 + (90 * j), 50 + (70 * i));
				theGang.push_back(new lvlOne_Easy(vec, alienEasyTexture));
				j++;
				theGang.push_back(new lvlOne_Hard(vec, alienHardLvlTexture));
				j++;
				theGang.push_back(new lvlOne_Easy(vec, alienEasyTexture));
			}
		}
	}

	else if (lvl == LEVEL_TWO_HARD)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Vector2f vec(135 + (90 * j), 50 + (70 * i));
				theGang.push_back(new lvlOne_Hard(vec, alienHardLvlTexture));
			}
		}
	}
	else if (lvl == HARBERT)
	{
		Vector2f vec(200, 300);
		theGang.push_back(new lvlOne_Easy(vec, alienEasyTexture));
	}
}

void alienGroupMgr::loadSavePos(Vector2f pos, difficultyType d)
{
	if (d == LEVEL_ONE_EASY)
		theGang.push_back(new lvlOne_Easy(pos, alienEasyTexture));
	else if (d == LEVEL_ONE_HARD)
		theGang.push_back(new lvlOne_Hard(pos, alienHardLvlTexture));
	else if (d == LEVEL_TWO_EASY)
		theGang.push_back(new lvlTwo_Easy(pos, alienHardLvlTexture));
	else if (d == LEVEL_TWO_HARD)
		theGang.push_back(new lvlTwo_Hard(pos, alienHardLvlTexture));

}

void alienGroupMgr::setLevel(difficultyType type)
{
	lvl = type;
}

