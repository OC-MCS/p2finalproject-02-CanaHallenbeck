#include "alien.h"



alien::alien(Vector2f pos, difficultyType d)
{
	xPos = pos.x;
	yPos = pos.y;
	lvl = d;
}


lvlOneCrook::lvlOneCrook(Vector2f pos, Texture & t) : alien(pos, LEVEL_ONE)
{
	lvlOneAlienSprite.setPosition(pos);
	lvlOneAlienSprite.setTexture(t);
}

void lvlOneCrook::draw(RenderWindow & win)
{
	win.draw(lvlOneAlienSprite);
}

Sprite & lvlOneCrook::getSprite()
{
	return lvlOneAlienSprite;
}

