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
#include "playerMgr.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf; 


int main()
{

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	window.setFramerateLimit(60);

	shotMgr shot;
	alienGroupMgr alien;
	player ship(window);

	int index,
		timer = 0,
		seconds = 0,
		minutes = 0,
		livesRemaining = 3,
		scoreCount = 0,
		highScore = 0;
	bool secSwitch = false,
		 death = false,
		 hit;


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

	while (window.isOpen())
	{
		if (livesRemaining > 0)
		{
				death = false;

				Event event;

				while (window.pollEvent(event))
				{

					if (event.type == Event::Closed)
						window.close();
					else if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::Space)
						{
							shot.shoot(MISSILE, ship.getSprite().getPosition());
						}
					}
				}

				hit = false;
				index = alien.disappear(shot, hit);
				shot.disappear(hit, index);

				ship.move();
				alien.sideMove(secSwitch);

				if (shot.getAmountFilled() > 0)
					shot.move();

				for (int i = 0; !death && i < alien.getAmountFilled(); i++)
				{
					FloatRect alienBound = alien.getlist(i)->getSprite().getGlobalBounds();
					
					if (alienBound.intersects(ship.getSprite().getGlobalBounds()))
					{
						death = true;
						livesRemaining--;
						ship.reset();
						alien.reset();

						if (scoreCount > highScore)
							highScore = scoreCount;

						scoreCount = 0;
					}
				}
				for (int i = 0; !death && i < shot.getAmountFilled(); i++)
				{
					FloatRect bulletBound = shot.getList(i)->getSprite().getGlobalBounds();

					if (bulletBound.intersects(ship.getSprite().getGlobalBounds()) 
						&& shot.getList(i)->getType() == BOMB)
					{
						death = true;
						ship.reset();
						alien.reset();
						hit = true;
						shot.disappear(hit, i);
						livesRemaining--;

						if (scoreCount > highScore)
							highScore = scoreCount;
						
						scoreCount = 0;
					}
				}

				if (!death)
				{
					if (hit)
						scoreCount += 100;

					if (timer == 30)
						alien.RandomDropBomb(shot);

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
					Text score("Score  " + to_string(scoreCount), font, 15);
					score.setPosition(10, 25);
					Text lives("Lives  " + to_string(livesRemaining), font, 15);
					lives.setPosition(10, 45);

					window.draw(background);   //  <--- ----- ----- -- background
					ship.draw(window);		   //  <---- ------ ---- ---- ship
					shot.draw(window);	       //  < ----- ----- ---- - missiles
					alien.draw(window);		   //  <- ----- ----- -----  aliens
					window.draw(time);         //  <-- ----- ----- ---- - time
					window.draw(score);		   //  <--- ----- ----- ----  score
					window.draw(lives);		   //  <---- ----- ----- ---  lives


					if (alien.getAmountFilled() == 0)
					{
						cout << "YOU WON!\nFINAL SCORE : " << scoreCount << endl;
						window.close();
					}

				}
				
				window.display();
		}
		else
		{
			cout << "YOU DIED!\nHIGH SCORE : " << highScore << endl;
			window.close();
		}

	}

	return 0;
}

