#include "alien.h"



alien::alien(Vector2f pos, difficultyType d)
{
	xPos = pos.x;
	yPos = pos.y;
	lvl = d;
}

lvlOne_Easy::lvlOne_Easy(Vector2f pos, Texture & t) : alien(pos, LEVEL_ONE_EASY)
{
	Easy_LvlOneAlienSprite.setPosition(pos);
	Easy_LvlOneAlienSprite.setTexture(t);

	AD.Difficulty = LEVEL_ONE_EASY;
	AD.XposLoc = pos.x;
	AD.YposLoc = pos.y;
}
void lvlOne_Easy::draw(RenderWindow & win)
{
	win.draw(Easy_LvlOneAlienSprite);
}
Sprite & lvlOne_Easy::getSprite()
{
	return Easy_LvlOneAlienSprite;
}

AlienData lvlOne_Easy::getFileRecord() const
{
	return AD;
}

lvlOne_Hard::lvlOne_Hard(Vector2f pos, Texture & t) : alien(pos, LEVEL_ONE_HARD)
{
	Hard_LvlOneAlienSprite.setPosition(pos);
	Hard_LvlOneAlienSprite.setTexture(t);

	AD.Difficulty = LEVEL_ONE_HARD;
	AD.XposLoc = pos.x;
	AD.YposLoc = pos.y;

}
void lvlOne_Hard::draw(RenderWindow & win)
{
	win.draw(Hard_LvlOneAlienSprite);
}
Sprite & lvlOne_Hard::getSprite()
{
	return Hard_LvlOneAlienSprite;
}

AlienData lvlOne_Hard::getFileRecord() const
{
	return AD;
}

lvlTwo_Easy::lvlTwo_Easy(Vector2f pos, Texture & t) : alien(pos, LEVEL_TWO_EASY)
{
	Easy_LvlTwoAlienSprite.setPosition(pos);
	Easy_LvlTwoAlienSprite.setTexture(t);

	AD.Difficulty = LEVEL_TWO_EASY;
	AD.XposLoc = pos.x;
	AD.YposLoc = pos.y;
}

void lvlTwo_Easy::draw(RenderWindow & win)
{
	win.draw(Easy_LvlTwoAlienSprite);
}

Sprite & lvlTwo_Easy::getSprite()
{
	return Easy_LvlTwoAlienSprite;
}

AlienData lvlTwo_Easy::getFileRecord() const
{
	return AD;
}

lvlTwo_Hard::lvlTwo_Hard(Vector2f pos, Texture & t) : alien(pos, LEVEL_TWO_HARD)
{
	Hard_LvlTwoAlienSprite.setPosition(pos);
	Hard_LvlTwoAlienSprite.setTexture(t);

	AD.Difficulty = LEVEL_TWO_HARD;
	AD.XposLoc = pos.x;
	AD.YposLoc = pos.y;
}

void lvlTwo_Hard::draw(RenderWindow & win)
{
	win.draw(Hard_LvlTwoAlienSprite);
}

Sprite & lvlTwo_Hard::getSprite()
{
	return Hard_LvlTwoAlienSprite;
}

AlienData lvlTwo_Hard::getFileRecord() const
{
	return AD;
}
