#pragma once
#include <iostream>
#include "playerMgr.h"
#include "shotMgr.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//struct playerData
//{
//
//};

class player
{
private:
	Sprite ship;
	Texture shipTexture, harbetModeTexture;
	float xPos, yPos;

public:
	player(RenderWindow& win);
	void move();
	void draw(RenderWindow& win);
	Sprite & getSprite() { return ship; }
	void reset();
	void shoot(player p, RenderWindow & win, shotMgr & shot);
	void setTexture();
};