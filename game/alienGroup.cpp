#include "alienGroup.h"
#include "shotMgr.h"
#include <iostream>
#include <ctime>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

alienGroupMgr::alienGroupMgr()
{
	if (!alienTexture.loadFromFile("alien2.png"))
	{
		cout << "Unable to load missile texture!" << endl;
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			Vector2f vec(135 + (90 * j), 50 + (70 * i));
			theGang.push_back(new lvlOneCrook(vec, alienTexture));
		}
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

		const float DISTANCE = 0.5f;	

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

			if (alienBound.intersects(bulletBound) && m.getList(i)->getType() == MISSILE)
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

void alienGroupMgr::RandomDropBomb(shotMgr& m)
{

		Vector2f loc;
		bool found = false;

		unsigned seed = time(0);
		srand(seed);

		const int MIN_VALUE = 1;
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
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			Vector2f vec(135 + (90 * j), 50 + (70 * i));
			theGang.push_back(new lvlOneCrook(vec, alienTexture));
		}
	}
}

