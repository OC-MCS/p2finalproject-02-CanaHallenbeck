//==========================================================================
// Cana Hallenbeck
//
//
//
//==========================================================================
#include <iostream>
#include "weapon.h"
#include "shotMgr.h"
#include "alienGroup.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf; 


void moveShip(Sprite& ship);

int main()
{

	shotMgr missile;
	alienGroupMgr alien;
	bool missileInFlight = false,
		secSwitch = false;
	int timer = 0,
		seconds = 0,
		minutes = 0,
		lives = 3,
		score = 0;

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	window.setFramerateLimit(60);


	Texture shipTexture;
	if (!shipTexture.loadFromFile("ship.png"))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Font font;
	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
	{
		cout << "Unable to load font" << endl;
		exit(EXIT_FAILURE);
	}

	Sprite background;
	background.setTexture(starsTexture);

	background.setScale(1.5, 1.5);

	Sprite ship;
	ship.setTexture(shipTexture);

	float shipX = window.getSize().x / 2.0f;
	float shipY = window.getSize().y / 1.08f;
	ship.setPosition(shipX, shipY);

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			 
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					missile.shoot(MISSILE, ship.getPosition());
					missileInFlight = true;
				}
			}
		}

		if (missileInFlight)
		{
			bool hit = false;
			int index = alien.disappear(missile, hit);
			missile.disappear(hit, index);

			if (hit)
			{
				score += 100;
			}

			if (missile.getAmountFilled() > 0)
			{
				missile.move();
			}
			else
			{
				missileInFlight = false;
			}

		}

		moveShip(ship);
		alien.sideMove(secSwitch);

		//-----------------------------------------------------------------make UI class
	
			if (timer < 60)
				timer++;
			else
			{
				seconds++;
				timer = 0;
				secSwitch ^= true;
			}
		    if (seconds == 60)
		    {
			    minutes++;
				seconds = 0;
		    }

		Text time("Time played   " + to_string(minutes) + " : " + to_string(seconds) + " : " + to_string(timer), font, 15);
		time.setPosition(10, 5);
		Text score("Score  " + to_string(score), font, 15);
		score.setPosition(10, 25);
		Text lives("Lives  " + to_string(lives), font, 15);
		lives.setPosition(10, 45);
		
	//-----------------------------------------------------------------------------


		window.draw(background);   //  <--- ----- ------ - background
		window.draw(ship);		   //  <---- ----- ----- ---- ship
		missile.draw(window);	   //  < ----- ----- ---- - missiles
		alien.draw(window);		   //  <- ----- ----- -----  aliens
		window.draw(time);         //  <-- ----- ----- ------ time
		window.draw(score);		   //  <--- ----- ----- ----  score
		window.draw(lives);		   //  <---- ----- ----- ---  lives


		window.display();

	}

	return 0;
}

void moveShip(Sprite& ship)
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

