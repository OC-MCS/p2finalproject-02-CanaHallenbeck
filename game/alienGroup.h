//----------------------------------------------------------
//	alien group -- 
//
//	a class that controls the actions of the alien as a group
//-----------------------------------------------------------

#pragma once
#include "alien.h"
#include "shotMgr.h"
#include <list>
using namespace std;

//
//struct AlienData
//{
//	float XposLoc,
//		YposLoc;
//	difficultyType Difficulty;
//};

class alienGroupMgr
{
private:

	difficultyType lvl = LEVEL_ONE_EASY;
	Texture alienEasyTexture, 
		    alienHardLvlTexture;
	list<alien*> theGang; // <----------------- list of ptrs to aliens
	bool wallSwitch = false; // <------------- which direction the aliens are moving

public:
	
	alienGroupMgr(); // loads textures

	void sideMove(bool time); // <-------------- moves aliens from side to side each frame
	void downMove(); // <----------------------- if wall hit, move down
	void RandomBombDrop(shotMgr& m); // <----------- random alien drops a bomb
	
	alien * getlist(int i); // <------------------------- returns alien at index
	int getAmountFilled() { return theGang.size(); } // <-------- return size of list
	difficultyType getType() { return lvl; } // <---------------- difficulty level

	void setLevel(difficultyType type); // <--------------------- set difficulty
	void draw(RenderWindow& win); // <-------------------------- draw aliens each frame
	int disappear(shotMgr m, bool& hit); // <------------------- delete aliens who were shot
	void reset(); // <------------------------------------------ return aliens to inition position
};