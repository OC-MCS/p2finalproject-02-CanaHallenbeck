//--------------------------------------------------------------------------
//	shot manager -- 
//
//	a class that controls the vector of shots fired by aliens or the player
//--------------------------------------------------------------------------

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
	vector<shot*> shotsFired; // a vector of ptrs to shotsFired (bullets and bombs)
	Texture missileTexture,   // texture of player attacks
		    bombTexture;      // texture of alien attacks
public:
	shotMgr(); // <------------ constructor; loads textures
	void shoot(attackType b_OR_m, Vector2f pos); // <----- adds to shot* vector
	void disappear(bool hit, int i); // <----------------- deletes bombs/missiles that hit something or flew offscreen
	void move(); // <---------------------------------------- moves the attacks on every frame
	void draw(RenderWindow& win); // <----------------------- draws the attacks on every frame
	int getAmountFilled() { return shotsFired.size(); } // <---------------- returns size of vector
	shot* getList(int i) { return shotsFired[i]; } // <------------------ returns vector location of index (particular bomb or missile)
	void reset(); // <------------------------------------------------ erase all shots fired
};