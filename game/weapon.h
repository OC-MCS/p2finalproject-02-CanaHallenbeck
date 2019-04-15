#pragma once
#include <vector>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

enum attackType { BOMB, MISSILE };

class shot
{
private:
	float xPos,
		  yPos;
	attackType bombOrMissile;
public:
	shot(Vector2f pos, attackType b_OR_m);
	virtual void draw(RenderWindow & win) = 0;
	virtual Sprite & getSprite() = 0;
	attackType getType() { return bombOrMissile; }
};

class missile : public shot
{
private:
	Sprite missileSprite;
public:
	missile(Vector2f pos, Texture & t);
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