#pragma once
#include <vector>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

enum difficultyType {LEVEL_ONE, LEVEL_TWO};

class alien
{
private:
	float xPos,
		  yPos;
	difficultyType lvl;
public:
	alien(Vector2f pos, difficultyType d);
	virtual void draw(RenderWindow & win) = 0;
	virtual Sprite & getSprite() = 0;
};

class lvlOneCrook : public alien
{
private:
	Sprite lvlOneAlienSprite;
public:
	lvlOneCrook(Vector2f pos, Texture & t);
	void draw(RenderWindow & win);
	Sprite & getSprite();
};