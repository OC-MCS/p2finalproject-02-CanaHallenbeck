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
	Texture t,
			t2;
public:
	menu();
	bool introScreen(RenderWindow& window);
	void levelSelect(RenderWindow& window, alienGroupMgr& a);
	void levelChoiceDisplay(RenderWindow& window, alienGroupMgr a, Texture backTexture);
	void victoryDisplay(RenderWindow & window, int score, int lives);
	void playAgainPrompt(RenderWindow & win);
	void saveGame(ostream & o, alienGroupMgr a, player p);
	void loadGame(istream & i, alienGroupMgr * a);
};