#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;


class player
{
private:
	Sprite ship;
	Texture shipTexture;
	float xPos, yPos;

public:
	player(RenderWindow& win);
	void move();
	void draw(RenderWindow& win);
	Sprite & getSprite() { return ship; }
	void reset();
};