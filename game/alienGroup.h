#pragma once
#include "alien.h"
#include "shotMgr.h"
#include <list>
using namespace std;

class alienGroupMgr
{
private:
	difficultyType lvl = LEVEL_ONE_EASY;
	Texture alienEasyTexture, 
		alienHardLvlTexture;
	list<alien*> theGang;
	bool wallSwitch = false;
public:
	alienGroupMgr();

	void sideMove(bool time);
	void downMove();
	void RandomBombDrop(shotMgr& m);
	
	alien * getlist(int i);
	int getAmountFilled() { return theGang.size(); }
	difficultyType getType() { return lvl; }

	void setLevel(difficultyType type);
	void draw(RenderWindow& win);
	int disappear(shotMgr m, bool& hit);
	void reset();
	void loadSavePos(Vector2f pos, difficultyType d);
};