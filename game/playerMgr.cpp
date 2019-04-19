#include "playerMgr.h"

player::player(RenderWindow & win)
{
	if (!shipTexture.loadFromFile("ship.png"))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}
	if (!harbetModeTexture.loadFromFile("ship2.png"))
	{
		cout << "Unable to load ship (2) texture!" << endl;
		exit(EXIT_FAILURE);
	}

	xPos = win.getSize().x / 2.0f;
	yPos = win.getSize().y / 1.08f;
	ship.setPosition(xPos, yPos);
	ship.setTexture(shipTexture);
}

void player::move()
{
	const float DISTANCE = 5.0f;
	Vector2f shipPos = ship.getPosition();

	if (Keyboard::isKeyPressed(Keyboard::Left) && shipPos.x > 0)
	{
		ship.move(-DISTANCE, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && shipPos.x < 778)
	{
		ship.move(DISTANCE, 0);
	}
}

void player::draw(RenderWindow & win)
{
	win.draw(ship);
}

void player::reset()
{
	ship.setPosition(xPos, yPos);
}

void player::shoot(player p, RenderWindow & window, shotMgr & shot)
{
	Event event;

	while (window.pollEvent(event))//																|
	{//																								|
		//																							|
		if (event.type == Event::Closed)//															|
			window.close(); //																		|
		else if (event.type == Event::KeyPressed)
		{//																							`---------------,
			if (event.key.code == Keyboard::Space)//																|
			{//																										|
				shot.shoot(MISSILE, p.getSprite().getPosition());//													|
			}//																										|
		}//																											|
	}//																												|

}

void player::setTexture()
{
	ship.setTexture(harbetModeTexture);
}
