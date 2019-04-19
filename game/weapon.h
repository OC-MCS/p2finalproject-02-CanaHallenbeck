//-------------------------------------------------------------
//	weapon -- 
//
//	a class that controls the data for alien and player attacks
//-------------------------------------------------------------

#pragma once
#include <vector>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

enum attackType { BOMB, MISSILE };

class shot // base class
{
private:
	float xPos,
		  yPos;
	attackType bombOrMissile;
public:
	shot(Vector2f pos, attackType b_OR_m); // <------ constructor
	virtual void draw(RenderWindow & win) = 0; // <------draw bullets on screen
	virtual Sprite & getSprite() = 0; // <------------- return sprite data
	attackType getType() { return bombOrMissile; } // <-------- return whether attack is bomb or missile)
};

class missile : public shot
{
private:
	Sprite missileSprite;
public:
	missile(Vector2f pos, Texture & t); // <------------- constructor; sets position and texture
	void draw(RenderWindow & win);
	Sprite & getSprite();
};

class bomb : public shot
{
private:
	Sprite bombSprite;
public:
	bomb(Vector2f pos, Texture & t);
	void draw(RenderWindow & win);
	Sprite & getSprite();
};