//----------------------------------------------------------------
//	menu UI -- 
//
//	a class in charge of menu option display (e.g. level select)
//----------------------------------------------------------------
#pragma once
#include <iostream>
#include "alienGroup.h"
#include "playerMgr.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class menu
{
private:
	Font font;
	Texture t, t2; // texture of aliens used as decoration on intro screen
public:
	menu();
	bool introScreen(RenderWindow& window); // <-------------------------------------- screen that displays when game first loads
	void levelSelect(RenderWindow& window, alienGroupMgr& a); // <---------------- screen that prompts for level selection
	void levelChoiceDisplay(RenderWindow& window, alienGroupMgr a, Texture backTexture); // <----- screen that displays before level begins
	void victoryDisplay(RenderWindow & window, int score, int lives); // <-------------------- screen that tells the user they won
	void deathDisplay(RenderWindow & window, int score); // <----------------------------------- screen that tells the user they died
	void playAgainPrompt(RenderWindow & win); // <----------------------------------------- screen that asks user if they want to play again
	//void saveGame(ostream & o, alienGroupMgr a, player p);
	//void loadGame(istream & i, alienGroupMgr* a);
};