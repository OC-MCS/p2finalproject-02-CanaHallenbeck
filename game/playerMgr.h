//----------------------------------------------------------
//	player manager -- 
//
//	a class in charge of the player's actions
//-----------------------------------------------------------
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
	Texture shipTexture;
	float xPos, yPos;

public:
	player(RenderWindow& win); // <------------------------ loads texture, set position and texture of ship
	void move(); // <------------------------------------- load position of player
	void draw(RenderWindow& win); // <-------------------- draw player every frame
	Sprite & getSprite() { return ship; } // <------------- return sprite data
	void reset(); // <------------------------------------- set to initial position
	void shoot(player p, RenderWindow & win, shotMgr & shot); // <------ if space pressed, shoot
};