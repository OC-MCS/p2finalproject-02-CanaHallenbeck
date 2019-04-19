//==========================================================================
// Cana Hallenbeck
// Programming II -- Due Friday, April 19
// Space invaders ft. Galaga sprites
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

	shotMgr shot; // shots fired by aliens or player
	alienGroupMgr alien; // aliens on screen
	player ship(window); // player sprite
	menu menu; // menu display funtions

	int bulletIndex, // index of the bullet that hit the alien
		timer = 0,   // counts the framerate
		seconds = 0, // seconds played (60 frames)
		minutes = 0, // minutes played (60 seconds)
		livesRemaining = 3, // lives that the player has until game-over
		scoreCount = 0, // score gained by killing enemies
		highScore = 0,  // highest score achieved during the game before dying
		returnToPreviousScore = 0; // score gained from previous levels (if past level one)
	bool secSwitch = false, // switches after a certain amount of frames for alien behavior
		 death = false, // did the player die?
		 hit, // was an alien hit?
		 toStartMenu = true, // return to intro screen
		 newGameOrLoadGame_SelectionMenu = true, // save or load game option (unfinished)
		 levelChoiceDisplay = true; // level selection menu


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

	Sprite background; // level backdrop
	background.setTexture(starsTexture);
	background.setScale(1.5, 1.5);


	while (window.isOpen())
	{
		//------------------------------------------- YOU CAN COMMENT OUT THIS WHOLE SECTION TO BUG TEST WITHOUT MENU --------.
		//																													  |
		if (toStartMenu)    //																								  |										 							
		{                   //																								  |																		
		newGameOrLoadGame_SelectionMenu = menu.introScreen(window);//														  |																		
		toStartMenu = false;//																								  |																			
		}//																													  |															
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
			levelChoiceDisplay = false;							 //															  |
		  //																												  |
		} //--------------------------------------------------------------------------------------------------------.---------`
		  //																										|
		else if (livesRemaining > 0) // (And change 'else if' to 'if')												|
		{																		            //						|
				death = false;																//						|
																							//						|
				for (int i = 0; !death && i < alien.getAmountFilled(); i++)					//						|
				{																			//						|
					FloatRect alienBound = alien.getlist(i)->getSprite().getGlobalBounds(); //						|
																							//						|
					if (alienBound.intersects(ship.getSprite().getGlobalBounds()) 			//						|
						|| alien.getlist(i)->getSprite().getPosition().y > 600)				//						|
					{																		//						|
						secSwitch = false;													//						|
						death = true;														//						|
						livesRemaining--;													//						|
						shot.reset();														//						|
						ship.reset();														//						|
						alien.reset();														//						|
																							//						|
						if (scoreCount > highScore)											//						|
							highScore = scoreCount;											//						|
																							//						|
						scoreCount = returnToPreviousScore;									//						|
					}																		//						|
				}																			//						|
				for (int i = 0; !death && i < shot.getAmountFilled(); i++)					//					    |
				{																			//		 			    |
					FloatRect bulletBound = shot.getList(i)->getSprite().getGlobalBounds();	//						|
																							//						|
					if (bulletBound.intersects(ship.getSprite().getGlobalBounds())			//_						|
						&& shot.getList(i)->getType() == BOMB)			//						|					|
					{													//						.					|
						secSwitch = false;			//											-					|
						death = true;				//											'					|
						hit = true;				    //																|
						livesRemaining--;			//																|
						shot.reset();				//																|
						ship.reset();				//																|
						alien.reset();				//																|
													//																|
						if (scoreCount > highScore) //																|
							highScore = scoreCount; //																|
													//													  			|
						scoreCount = returnToPreviousScore; //														|
					}//																								|
				}	 //																								|
				if (!death)//																						|
				{		   //																					    |
					ship.shoot(ship, window, shot);		//															`---------------,
														//																			|
					hit = false;							  //																	|
					bulletIndex = alien.disappear(shot, hit); //																	|
					shot.disappear(hit, bulletIndex);		  //																	|
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
					time.setPosition(10, 5);   //																											|
					Text score("Score  " + to_string(scoreCount), font, 15); //																				|
					score.setPosition(10, 25); //																											|
					Text lives("Lives  " + to_string(livesRemaining), font, 15); //																			|
					lives.setPosition(10, 45); //																											|
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
						returnToPreviousScore = (scoreCount + (50 * livesRemaining));			//														|	|
						menu.victoryDisplay(window, returnToPreviousScore, livesRemaining); 	//	      <<------------------------------------------------|
						//																																	|
						if (alien.getType() == LEVEL_TWO_EASY || alien.getType() == LEVEL_TWO_HARD || HARBERT)	//											|
						{																						//				THESE TOO					|
							toStartMenu = true;																	//											|
																												//											|
							newGameOrLoadGame_SelectionMenu = true;												//											|
							menu.playAgainPrompt(window); // << ---------------------------------------------------------------,----------------------------
						}							//																		   |
						levelChoiceDisplay = true;  //																		   |
						livesRemaining = 3;			//																		   |
													//																		   |
						if (alien.getType() == LEVEL_ONE_EASY)		//														   |
							alien.setLevel(LEVEL_TWO_EASY);			//														   |
						else if (alien.getType() == LEVEL_ONE_HARD)	//														   |
							alien.setLevel(LEVEL_TWO_HARD);			//														   |
										//																					   |
						alien.reset();	//																					   |
						shot.reset();	//																					   |
						ship.reset(); 	//																					   |
					}					//																,----------------------`
					//																				   |
				}	//																				   |
				//																					   |
				window.display();  		//														   	   |
		}//																							   |
		else									 //													   |
		{									     //												  	   |
			menu.deathDisplay(window, highScore);//  <<------------------------------------------,-----`
			menu.playAgainPrompt(window); // << -------------------------------------------------`
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
	//--------------------------------------------------------------------------------------------------------------
	// TIMER FUNTION -- Controls everything managed acording to framerate
	//--------------------------------------------------------------------------------------------------------------

	if (alien.getType() == LEVEL_ONE_EASY || alien.getType() == LEVEL_TWO_EASY)
	{
		if (timer == 30)
			alien.RandomBombDrop(shot);
	}
	else if(alien.getType() == LEVEL_ONE_HARD || alien.getType() == LEVEL_TWO_HARD)
	{
		if (timer == 30 || timer == 60)
			alien.RandomBombDrop(shot);
	}

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