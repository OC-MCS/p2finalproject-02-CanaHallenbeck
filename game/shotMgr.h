#pragma once
#include <iostream>
#include <list>
#include "weapon.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;


class shotMgr
{
private:
	vector<shot*> shotsFired;
	Texture missileTexture,
		    bombTexture;
public:
	shotMgr();
	void shoot(attackType b_OR_m, Vector2f pos);
	void disappear(bool hit, int i);
	void move();
	void draw(RenderWindow& win);
	int getAmountFilled() { return shotsFired.size(); }
	shot* getList(int i) { return shotsFired[i]; }
	void reset();
};