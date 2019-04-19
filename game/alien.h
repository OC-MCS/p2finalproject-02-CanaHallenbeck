//-------------------------------------------------------------
//	alien -- 
//
//	a class that controls the data for each individual alien
//-----------------------------------------------------------

#pragma once
#include <vector>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

enum difficultyType {LEVEL_ONE_EASY, LEVEL_TWO_EASY, LEVEL_ONE_HARD, LEVEL_TWO_HARD, HARBERT}; // difficulty level


class alien // base class
{
private:
	float xPos,
		  yPos;
	difficultyType lvl;
public:
	alien(Vector2f pos, difficultyType d); // <------------ sets position and texture
	virtual void draw(RenderWindow & win) = 0; // <-------- draws aliens on screen
	virtual Sprite & getSprite() = 0; //   <--------------- returns alien sprite data
	difficultyType getType() { return lvl; } // <---------- returns alien level
};

class lvlOne_Easy : public alien
{
private:
	Sprite Easy_LvlOneAlienSprite;
public:
	lvlOne_Easy(Vector2f pos, Texture & t);
	void draw(RenderWindow & win);
	Sprite & getSprite();
};

class lvlTwo_Easy : public alien
{
private: 
	Sprite Easy_LvlTwoAlienSprite;
public:
	lvlTwo_Easy(Vector2f pos, Texture & t);
	void draw(RenderWindow & win);
	Sprite & getSprite();
};

class lvlOne_Hard : public alien
{
private:
	Sprite Hard_LvlOneAlienSprite;
public:
	lvlOne_Hard(Vector2f pos, Texture & t);
	void draw(RenderWindow & win);
	Sprite & getSprite();
};

class lvlTwo_Hard : public alien
{
private:
	Sprite Hard_LvlTwoAlienSprite;
public:
	lvlTwo_Hard(Vector2f pos, Texture & t);
	void draw(RenderWindow & win);
	Sprite & getSprite();
};

class harbertMode_SUPER_DIFFICULT : public alien
{
private:
	Sprite harbertModeSprite;
public:
	harbertMode_SUPER_DIFFICULT(Vector2f pos, Texture & t);
	void draw(RenderWindow & win);
	Sprite & getSprite();
};