#include "shotMgr.h"
using namespace std;

shotMgr::shotMgr()
{
	if (!missileTexture.loadFromFile("missile.png"))
	{
		cout << "Unable to load missile texture!" << endl;
		exit(EXIT_FAILURE);
	}
	if (!bombTexture.loadFromFile("bomb.png"))
	{
		cout << "Unable to load bomb texture!" << endl;
		exit(EXIT_FAILURE);
	}
}

void shotMgr::shoot(attackType b_OR_m, Vector2f pos)
{
	if(b_OR_m == MISSILE)
	shotsFired.push_back(new missile(pos, missileTexture));
	else
	shotsFired.push_back(new bomb(pos, bombTexture));
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
}

void shotMgr::move()
{
	const float DISTANCE = 6.0f;

	for (int i = 0; i < shotsFired.size(); i++)
	{
		if (shotsFired[i]->getType() == MISSILE)
		{
			shotsFired[i]->getSprite().move(0, -DISTANCE);
		}
		else
		{
		    shotsFired[i]->getSprite().move(0, DISTANCE);
		}
	}

}

void shotMgr::draw(RenderWindow & win)
{

	for (int i = 0; i < shotsFired.size(); i++)
	{
		shotsFired[i]->draw(win);
	}
}

void shotMgr::reset()
{
	for( int i = 0; i < shotsFired.size(); i++)
	{
		shotsFired.erase(shotsFired.begin() + i);
	}
}




