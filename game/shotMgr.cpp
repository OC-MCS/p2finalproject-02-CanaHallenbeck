#include "shotMgr.h"
using namespace std;

shotMgr::shotMgr()
{
	if (!missileTexture.loadFromFile("missile.png"))
	{
		cout << "Unable to load missile texture!" << endl;
		exit(EXIT_FAILURE);
	}
}

void shotMgr::shoot(attackType b_OR_m, Vector2f pos)
{
	if(b_OR_m == MISSILE)
	shotsFired.push_back(new missile(pos, missileTexture));
	else
	shotsFired.push_back(new bomb(pos, missileTexture));
}

void shotMgr::disappear(bool hit, int index)
{
	if (hit)
	{
		shotsFired.erase(shotsFired.begin() + index);
	}
	else
	{
		for (int i = 0; i < shotsFired.size(); i++)
		{
			if (shotsFired[i]->getSprite().getPosition().y < 0
			|| shotsFired[i]->getSprite().getPosition().y > 600)
			{
				shotsFired.erase(shotsFired.begin() + i);
			}

		}
	}


	//for (list<shot*>::iterator iter = shotsFired.begin(); iter != shotsFired.end();)
	//{
	//	shot* ptrShot = *iter;

	//	if (ptrShot->getSprite().getPosition().y < 0)
	//	{
	//		iter = shotsFired.erase(iter);
	//	}
	//	else
	//	{
	//		iter++;
	//	}
	//}
}

void shotMgr::move()
{

	for (int i = 0; i < shotsFired.size(); i++)
	{
		const float DISTANCE = 6.0f;
		shotsFired[i]->getSprite().move(0, -DISTANCE);
	}

	//for (list<shot*>::iterator iter = shotsFired.begin(); iter != shotsFired.end(); iter++)
	//{
	//	shot* ptrShot = *iter;

	//	const float DISTANCE = 6.0f;
	//	ptrShot->getSprite().move(0, -DISTANCE);
	//}
}

void shotMgr::draw(RenderWindow & win)
{

	for (int i = 0; i < shotsFired.size(); i++)
	{
		shotsFired[i]->draw(win);
	}

	//for (list<shot*>::iterator iter = shotsFired.begin(); iter != shotsFired.end(); iter++)
	//{
	//	shot* ptrShot = *iter;

	//	ptrShot->draw(win);
	//}
}




