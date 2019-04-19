//==========================================================================
// Cana Hallenbeck
// Programming II -- Due Friday, April 19
// Space invaders ft. Galaga sprites
//
//==========================================================================

#include <iostream>
#include <fstream>
#include "weapon.h"
#include "shotMgr.h"
#include "alienGroup.h"
#include "playerMgr.h"
#include "menuUI.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf; 

void timerFunctions(alienGroupMgr & alien, shotMgr & shot, int & timer, int & seconds, int & minutes, bool & secSwitch);

int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	window.setFramerateLimit(60);

	shotMgr shot;
	alienGroupMgr alien;
	player ship(window);
	menu menu;

	int index,
		timer = 0,
		seconds = 0,
		minutes = 0,
		livesRemaining = 3,
		scoreCount = 0,
		highScore = 0,
		returnToPreviousScore = 0;
	bool secSwitch = false,
		 death = false,
		 hit,
		 toStartMenu = true,
		 newGameOrLoadGame_SelectionMenu = true,
		 levelChoiceDisplay = true;


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


	//ifstream read;
	//read.open("shapes.bin", ios::in | ios::binary);

	//if (!read)
	//{
	//	cout << "file Open Failure" << endl;
	//	EXIT_FAILURE;
	//}
	//else
	//{
	//	menu.loadGame(read, &alien);
	//}

	//read.close();

	//ofstream write;
	//write.open("shapes.bin", ios::out | ios::binary);
	//if (!write)
	//{
	//	cout << "file Open Failure" << endl;
	//	EXIT_FAILURE;
	//}

	while (window.isOpen())
	{

		//------------------------------------------- YOU CAN COMMENT OUT THIS WHOLE SECTION TO BUG TEST WITHOUT MENU --------.------------ REPLACE WITH THIS CODE FOR MORE GENERIC LEVEL INTERFACE -----,
		//																													  |																			 |
		if (toStartMenu)    //																								  |										 									 |
		{                   //																								  |																			 |
		newGameOrLoadGame_SelectionMenu = menu.introScreen(window);//														  |																			 |
		toStartMenu = false;//																								  |																			 |
		}//																													  |																<------------`
		else if (newGameOrLoadGame_SelectionMenu)   //															  			  |
		{											//																		  |
			menu.levelSelect(window, alien);		//							( MENU UI CLASS )							  |							
			newGameOrLoadGame_SelectionMenu = false;//																		  |
			shot.reset(); //																								  |
			ship.reset(); //																								  |
			alien.reset();//																								  |
		}//																													  |
		else if (levelChoiceDisplay)//																						  |
		{//																													  |
			menu.levelChoiceDisplay(window, alien, starsTexture);//											    			  |
			levelChoiceDisplay = false;//																					  |
		  //																												  |
		} //------------------------------------------------------------------------------------------------------------------`

		else if (livesRemaining > 0) // (And change 'else if' to 'if')
		{
				death = false;

				for (int i = 0; !death && i < alien.getAmountFilled(); i++)
				{
					FloatRect alienBound = alien.getlist(i)->getSprite().getGlobalBounds();

					if (alienBound.intersects(ship.getSprite().getGlobalBounds()))
					{
						secSwitch = false;
						death = true;
						livesRemaining--;
						shot.reset();
						ship.reset();
						alien.reset();

						if (scoreCount > highScore)
							highScore = scoreCount;

						scoreCount = returnToPreviousScore;
					}
				}
				for (int i = 0; !death && i < shot.getAmountFilled(); i++)
				{
					FloatRect bulletBound = shot.getList(i)->getSprite().getGlobalBounds();

					if (bulletBound.intersects(ship.getSprite().getGlobalBounds())
						&& shot.getList(i)->getType() == BOMB)
					{
						secSwitch = false;
						death = true;
						hit = true;
						livesRemaining--;
						shot.reset();
						ship.reset();
						alien.reset();
													//																|
						if (scoreCount > highScore) //																|
							highScore = scoreCount; //																|
													//													  			|
						scoreCount = returnToPreviousScore; //														|
					}//																								|
				}	 //																								|
				if (!death)//																						|
				{//																									|
					ship.shoot(ship, window, shot);		//															`---------------,
					//																												|
					hit = false; //																									|
					index = alien.disappear(shot, hit); //																			|
					shot.disappear(hit, index); //																					|
					//																												|
					ship.move(); //																								    |
					alien.sideMove(secSwitch); //																				    |
											   //																					 `----------------------,
					if (shot.getAmountFilled() > 0) //																										|
						shot.move(); //																														|
									 //																														|
					if (hit && alien.getType() == LEVEL_ONE_EASY || hit && alien.getType() == LEVEL_TWO_EASY) //											|
						scoreCount += 100; //																												|
					else if (hit && alien.getType() == LEVEL_ONE_HARD || hit && alien.getType() == LEVEL_TWO_HARD) //										|
						scoreCount += 200; //																												|
					//																																		|
					timerFunctions(alien, shot, timer, seconds, minutes, secSwitch); //																		|
					//																																		|
					//																																		|
					Text time("Time played   " + to_string(minutes) + " : " + to_string(seconds) + " : " + to_string(timer), font, 15); //				    |
					time.setPosition(10, 5); //																												|
					Text score("Score  " + to_string(scoreCount), font, 15); //																				|
					score.setPosition(10, 25); //																											|
					Text lives("Lives  " + to_string(livesRemaining), font, 15); //																			|
					lives.setPosition(10, 45);//																											|
					//																																		|
					window.draw(background);   //  <--- ----- ----- -- background																		    |
					ship.draw(window);		   //  <---- ------ ---- ---- ship																				|
					shot.draw(window);	       //  < ----- ----- ---- - missiles																		    |
					alien.draw(window);		   //  <- ----- ----- ----- - aliens																		    |
					window.draw(time);         //  <-- ----- ----- ----- -time																				|
					window.draw(score);		   //  <--- ----- ----- ----- score																				|
					window.draw(lives);		   //  <---- ----- ----- ---- lives																			    |
					//																																		|
					//																																		|
					if (alien.getAmountFilled() == 0)	//																									|
					{									//																								 ---|
						returnToPreviousScore = (scoreCount + (50 * livesRemaining));			//							THIS LINE, TOO				|	|
						menu.victoryDisplay(window, returnToPreviousScore, livesRemaining); 	//	      <<-------------------------------------------------															|	|
						
						if (alien.getType() == LEVEL_TWO_EASY || alien.getType() == LEVEL_TWO_HARD)
						{
							toStartMenu = true;
							newGameOrLoadGame_SelectionMenu = true;
							menu.playAgainPrompt(window);
						}
					
						levelChoiceDisplay = true;
						livesRemaining = 3; 

						if (alien.getType() == LEVEL_ONE_EASY)
							alien.setLevel(LEVEL_TWO_EASY);
						else if (alien.getType() == LEVEL_ONE_HARD)
							alien.setLevel(LEVEL_TWO_HARD);
						
						alien.reset();
						shot.reset();
						ship.reset();
					}

				}
				
				window.display();
		}
		else
		{
			menu.playAgainPrompt(window);
			toStartMenu = true;
			newGameOrLoadGame_SelectionMenu = true;
			levelChoiceDisplay = true;
			livesRemaining = 3;
			alien.reset();
			shot.reset();
			ship.reset();
		}

	}

	return 0;
}

void timerFunctions(alienGroupMgr & alien, shotMgr & shot, int & timer, int & seconds, int & minutes, bool & secSwitch)
{

	if (timer == 30)
		alien.RandomBombDrop(shot);

	if (timer < 60)
		timer++;
	else
	{
		seconds++;
		timer = 0;
		secSwitch = !secSwitch;
	}

	if (seconds == 60)
	{
		minutes++;
		seconds = 0;
	}

}