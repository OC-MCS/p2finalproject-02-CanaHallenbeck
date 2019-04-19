#include "menuUI.h"
#include <iostream>
#include "alienGroup.h"
#include "playerMgr.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

menu::menu()
{

	if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
	{
		cout << "Unable to load font" << endl;
		exit(EXIT_FAILURE);
	}
	if (!t.loadFromFile("alien.png"))
	{
		cout << "Unable to load alien texture!" << endl;
		exit(EXIT_FAILURE);
	}
	if (!t2.loadFromFile("alien2.png"))
	{
		cout << "Unable to load alien texture!" << endl;
		exit(EXIT_FAILURE);
	}

}

bool menu::introScreen(RenderWindow& window)
{

	Vector2f spritePos(220, 155), spritePos2(520, 155);
	Sprite alienD_0,
		   alienD_1;

	Text alienTitle("ALIENS", font, 60);
	alienTitle.setPosition(285, 145);
	Text instructions("Press the right and left arrow keys to move\n\t\tPress the space bar to shoot", font, 20);
	instructions.setPosition(205, 300);
	Text continueTextPromt("PRESS ANY KEY TO CONTINUE", font, 20);
	continueTextPromt.setPosition(234, 400);
	Text newGameButton("\t  NEW GAME", font, 20);
	newGameButton.setPosition(290, 290);
	Text loadGameButton("\t  LOAD GAME", font, 20);
	loadGameButton.setPosition(288, 350);

	RectangleShape outline;
	outline.setPosition(25, 40);
	outline.setOutlineColor(Color::White);
	outline.setOutlineThickness(3);
	outline.setSize(Vector2f(750, 500));
	outline.setFillColor(Color::Transparent);

	alienD_0.setTexture(t);
	alienD_0.setPosition(spritePos);
	alienD_1.setTexture(t);
	alienD_1.setPosition(spritePos2);

	bool wait = true,
		newGameOrLoadGame = false;
	int count = 0;

	while (wait)
	{
		window.clear();
		window.draw(outline);
		window.draw(alienTitle);
		window.draw(alienD_0);
		window.draw(alienD_1);
		window.draw(instructions);

		if (count > 40 && count < 60)
			continueTextPromt.setFillColor(Color::Black);
		else if (count > 60)
		{
			count = 0;
			continueTextPromt.setFillColor(Color::White);
		}

		window.draw(continueTextPromt);
		window.display();

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
				wait = false;
		}

		count++;
	}

	wait = true;

	alienTitle.setFillColor(Color::Yellow);
	alienTitle.setPosition(285, 155);

	while (!newGameOrLoadGame)
	{
		window.clear();

		Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

		Event event;


		if (newGameButton.getGlobalBounds().contains(mousePos))
		{
			newGameButton.setFillColor(Color::Yellow);
			loadGameButton.setFillColor(Color::White);
			while (window.pollEvent(event))
			{
				 if (event.type == Event::MouseButtonReleased)
				{
					wait = false;
					newGameOrLoadGame = true;
				}
			}
		}
		else if (loadGameButton.getGlobalBounds().contains(mousePos))
		{
			newGameButton.setFillColor(Color::White);
			loadGameButton.setFillColor(Color::Yellow);
			while (window.pollEvent(event))
			{
				if (event.type == Event::MouseButtonReleased)
				{
					wait = false;
					newGameOrLoadGame = true;
				}
			}
		}

			window.draw(alienTitle);
			window.draw(outline);
			window.draw(newGameButton);
			window.draw(loadGameButton);
			window.display();

	}

	return newGameOrLoadGame;
}

void menu::levelSelect(RenderWindow & window, alienGroupMgr & a)
{

	RectangleShape outline;
	outline.setPosition(25, 40);
	outline.setOutlineColor(Color::White);
	outline.setOutlineThickness(3);
	outline.setSize(Vector2f(750, 500));
	outline.setFillColor(Color::Transparent);

	Text DifficultyHeader("SELECT DIFFICULTY", font, 30);
	DifficultyHeader.setPosition(250, 145);
	Text easyButton("\t   EASY", font, 20);
	easyButton.setPosition(310, 290);
	Text hardButton("\t   HARD", font, 20);
	hardButton.setPosition(310, 350);
	Text HarbetModeButton("\t   HARBERT", font, 20);
	HarbetModeButton.setPosition(295, 410);

	bool wait = true;

	while (wait)
	{
		window.clear();
		window.draw(DifficultyHeader);
		window.draw(outline);
		window.draw(easyButton);
		window.draw(hardButton);
		window.draw(HarbetModeButton);

		Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

		Event event;

		if (easyButton.getGlobalBounds().contains(mousePos))
		{
			easyButton.setFillColor(Color::Yellow);
			hardButton.setFillColor(Color::White);
			HarbetModeButton.setFillColor(Color::White);
			
			while (window.pollEvent(event))
			{	
				if (event.type == Event::MouseButtonReleased)
				{
					wait = false;
					a.setLevel(LEVEL_ONE_EASY);
				}
			}
		}
		else if (hardButton.getGlobalBounds().contains(mousePos))
		{
			easyButton.setFillColor(Color::White);
			hardButton.setFillColor(Color::Yellow);
			HarbetModeButton.setFillColor(Color::White);

			while (window.pollEvent(event))
			{
				if (event.type == Event::MouseButtonReleased)
				{
					wait = false;
					a.setLevel(LEVEL_ONE_HARD);
				}
			}
		}
		else if (HarbetModeButton.getGlobalBounds().contains(mousePos))
		{
			easyButton.setFillColor(Color::White);
			hardButton.setFillColor(Color::White);
			HarbetModeButton.setFillColor(Color::Yellow);
			
			while (window.pollEvent(event))
			{
				if (event.type == Event::MouseButtonReleased)
				{
					wait = false;
					a.setLevel(HARBERT);
				}
			}
		}

		window.display();

	}
}

void menu::levelChoiceDisplay(RenderWindow & window, alienGroupMgr a, Texture backTexture)
{
	Sprite background,
			alienD_0,
			alienD_1;
	background.setTexture(backTexture);
	background.setScale(1.5, 1.5);

	Vector2f spritePos(200, 155), 
			 spritePos2(410, 155);

	alienD_0.setTexture(t);
	alienD_0.setPosition(spritePos);
	alienD_1.setTexture(t2);
	alienD_1.setPosition(spritePos2);

	Text LevelOneHeader("LEVEL ONE", font, 30);
	LevelOneHeader.setPosition(300, 300);
	Text LevelTwoHeader("LEVEL TWO", font, 30);
	LevelTwoHeader.setPosition(300, 300);
	
	Text pointIndicator_0("= 100", font, 30);
	pointIndicator_0.setPosition(270, 155);
	Text pointIndicator_1("= 200", font, 30);
	pointIndicator_1.setPosition(470, 155);
	Text pointIndicator_2("+ 50 PER REMAINING LIFE", font, 20);
	pointIndicator_2.setPosition(250, 400);
	pointIndicator_2.setFillColor(Color::Yellow);

	int count = 0;
	bool wait = true;


	if (a.getType() == LEVEL_ONE_EASY || a.getType() == LEVEL_ONE_HARD)
	{
		while (wait)
		{
			window.clear();
			window.draw(background);
			window.draw(LevelOneHeader);
			window.draw(alienD_0);
			window.draw(alienD_1);
			window.draw(pointIndicator_0);
			window.draw(pointIndicator_1);
			window.draw(pointIndicator_2);

			window.display();

			count++;
			if (count > 120)
				wait = false;;
		}
	}
	else if (a.getType() == LEVEL_TWO_EASY || a.getType() == LEVEL_TWO_HARD)
	{
		while (wait)
		{
			window.clear();
			window.draw(background);
			window.draw(LevelTwoHeader);
			window.draw(alienD_0);
			window.draw(alienD_1);
			window.draw(pointIndicator_0);
			window.draw(pointIndicator_1);

			window.display();

			count++;
			if (count > 120)
				wait = false;;
		}
	}

}

void menu::victoryDisplay(RenderWindow & window, int score, int lives)
{
	bool wait = true;
	int count = 0;
	
	Text continueTextPromt("PRESS ANY KEY TO CONTINUE", font, 20);
	continueTextPromt.setPosition(234, 400);
	Text VictoryHeader("VICTORY", font, 60);
	VictoryHeader.setPosition(270, 145);
	Text LivesRemaining("\tLIVES REMAINING :  " + to_string(lives), font, 20);
	LivesRemaining.setPosition(270, 290);
	Text PointDisplay("\tSCORE : " + to_string(score), font, 20);
	PointDisplay.setPosition(310, 350);

	RectangleShape outline;
	outline.setPosition(25, 40);
	outline.setOutlineColor(Color::White);
	outline.setOutlineThickness(3);
	outline.setSize(Vector2f(750, 500));
	outline.setFillColor(Color::Transparent);

	while (wait)
	{
		window.clear();
		window.draw(outline);
		window.draw(VictoryHeader);
		window.draw(LivesRemaining);
		window.draw(PointDisplay);
		window.display();

		count++;
		if (count > 170)
			wait = false;;
	}
	
	wait = true;
	count = 0;
	
	while (wait)
	{
		window.clear();
		window.draw(outline);
		window.draw(VictoryHeader);
		window.draw(PointDisplay);
		window.draw(LivesRemaining);
		window.draw(continueTextPromt);
		window.display();

		if (count > 40 && count < 60)
			continueTextPromt.setFillColor(Color::Black);
		else if (count > 60)
		{
			count = 0;
			continueTextPromt.setFillColor(Color::White);
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				wait = false;
			}

		}

		count++;
	}	

}

void menu::deathDisplay(RenderWindow & window, int score)
{
	bool wait = true;
	int count = 0;

	Text continueTextPromt("PRESS ANY KEY TO CONTINUE", font, 20);
	continueTextPromt.setPosition(234, 400);
	Text VictoryHeader("YOU DIED", font, 60);
	VictoryHeader.setPosition(230, 145);
	Text PointDisplay("\HIGEST SCORE : " + to_string(score), font, 20);
	PointDisplay.setPosition(290, 350);

	RectangleShape outline;
	outline.setPosition(25, 40);
	outline.setOutlineColor(Color::White);
	outline.setOutlineThickness(3);
	outline.setSize(Vector2f(750, 500));
	outline.setFillColor(Color::Transparent);

	while (wait)
	{
		window.clear();
		window.draw(outline);
		window.draw(VictoryHeader);
		window.draw(PointDisplay);
		window.display();

		count++;
		if (count > 170)
			wait = false;;
	}

	wait = true;
	count = 0;

	while (wait)
	{
		window.clear();
		window.draw(outline);
		window.draw(VictoryHeader);
		window.draw(PointDisplay);
		window.draw(continueTextPromt);
		window.display();

		if (count > 40 && count < 60)
			continueTextPromt.setFillColor(Color::Black);
		else if (count > 60)
		{
			count = 0;
			continueTextPromt.setFillColor(Color::White);
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				wait = false;
			}

		}

		count++;
	}
}

void menu::playAgainPrompt(RenderWindow & window)
{

	bool wait = true;
	int count = 0;

	Text yesButton("YES", font, 20);
	yesButton.setPosition(400, 350);
	Text noButton("NO", font, 20);
	noButton.setPosition(330, 350);
	Text promptHeader("PLAY AGAIN?", font, 60);
	promptHeader.setPosition(200, 200);

	RectangleShape outline;
	outline.setPosition(25, 40);
	outline.setOutlineColor(Color::White);
	outline.setOutlineThickness(3);
	outline.setSize(Vector2f(750, 500));
	outline.setFillColor(Color::Transparent);


	while (wait)
	{
		window.clear();

		Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
		Event event;

		if (yesButton.getGlobalBounds().contains(mousePos))
		{
			yesButton.setFillColor(Color::Yellow);
			noButton.setFillColor(Color::White);
			while (window.pollEvent(event))
			{
				if (event.type == Event::MouseButtonReleased)
				{
					wait = false;
				}
			}
		}
		else if (noButton.getGlobalBounds().contains(mousePos))
		{
			yesButton.setFillColor(Color::White);
			noButton.setFillColor(Color::Yellow);
			while (window.pollEvent(event))
			{
				 if (event.type == Event::MouseButtonReleased)
				{
					window.close();
					cout << "Thanks for playing" << endl;
				}
			}
		}

		window.draw(yesButton);
		window.draw(noButton);
		window.draw(promptHeader);
		window.display();
	}

}

//void menu::saveGame(ostream & o, alienGroupMgr a, player p)
//{
//	for (int i = 0; i < a.getAmountFilled(); i++)
//	{
//		o.write(reinterpret_cast<char*>(&a.getlist(i)->getFileRecord()),
//			sizeof(a.getlist(i)->getFileRecord()));
//	}
//}

//
//void menu::loadGame(istream & in, alienGroupMgr *a)
//{
//	difficultyType tempLvl = LEVEL_ONE_EASY;
//	Vector2f loc(0, 0);
//	
//
//	while (in.read(reinterpret_cast<char*>(&tempLvl), sizeof(AlienData)))
//	{
//		loc.x = tempData.XposLoc;
//		loc.y = tempData.YposLoc;
//		tempLvl = tempData.Difficulty;
//		a->loadSavePos(loc, tempLvl);
//	}
//
//	a->setLevel(tempLvl);
//}

