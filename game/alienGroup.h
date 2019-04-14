#pragma once
#include "alien.h"
#include "shotMgr.h"
#include <list>
using namespace std;

class alienGroupMgr
{
private:
	Texture alienTexture;
	list<alien*> theGang;
	bool wallSwitch = false;
public:
	alienGroupMgr();
	void draw(RenderWindow& win);
	void sideMove(bool time);
	void downMove();
	int disappear(shotMgr m, bool& hit);
};