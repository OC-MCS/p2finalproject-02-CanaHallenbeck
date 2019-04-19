#include "alien.h"

//-------------------------------------------------------------
//	alien -- 
//
//	a class that controls the data for each individual alien
//-----------------------------------------------------------

alien::alien(Vector2f pos, difficultyType d)
{
	xPos = pos.x;
	yPos = pos.y;
	lvl = d;
}

lvlOne_Easy::lvlOne_Easy(Vector2f pos, Texture & t) : alien(pos, LEVEL_ONE_EASY) // set position
{
	Easy_LvlOneAlienSprite.setPosition(pos);
	Easy_LvlOneAlienSprite.setTexture(t);
}
void lvlOne_Easy::draw(RenderWindow & win) // draw on screen
{
	win.draw(Easy_LvlOneAlienSprite);
}
Sprite & lvlOne_Easy::getSprite() // return sprite data
{
	return Easy_LvlOneAlienSprite;
}

lvlOne_Hard::lvlOne_Hard(Vector2f pos, Texture & t) : alien(pos, LEVEL_ONE_HARD) // set position  & texture
{
	Hard_LvlOneAlienSprite.setPosition(pos);
	Hard_LvlOneAlienSprite.setTexture(t);

}
void lvlOne_Hard::draw(RenderWindow & win) // draw on screen
{ 
	win.draw(Hard_LvlOneAlienSprite);
}
Sprite & lvlOne_Hard::getSprite() // return sprite data
{
	return Hard_LvlOneAlienSprite;
}

lvlTwo_Easy::lvlTwo_Easy(Vector2f pos, Texture & t) : alien(pos, LEVEL_TWO_EASY) // set position & texture
{
	Easy_LvlTwoAlienSprite.setPosition(pos);
	Easy_LvlTwoAlienSprite.setTexture(t);
}

void lvlTwo_Easy::draw(RenderWindow & win)   // draw on screen
{
	win.draw(Easy_LvlTwoAlienSprite);
}

Sprite & lvlTwo_Easy::getSprite() // return sprite data
{
	return Easy_LvlTwoAlienSprite;
}


lvlTwo_Hard::lvlTwo_Hard(Vector2f pos, Texture & t) : alien(pos, LEVEL_TWO_HARD) // set position  & texture
{
	Hard_LvlTwoAlienSprite.setPosition(pos);
	Hard_LvlTwoAlienSprite.setTexture(t);
}

void lvlTwo_Hard::draw(RenderWindow & win)  // draw on screen
{
	win.draw(Hard_LvlTwoAlienSprite);
}

Sprite & lvlTwo_Hard::getSprite() // return sprite data
{
	return Hard_LvlTwoAlienSprite;
}

harbertMode_SUPER_DIFFICULT::harbertMode_SUPER_DIFFICULT(Vector2f pos, Texture & t) : alien(pos, HARBERT) // set position & texture
{
	harbertModeSprite.setPosition(pos);
	harbertModeSprite.setTexture(t);
}

void harbertMode_SUPER_DIFFICULT::draw(RenderWindow & win)  // draw on screen
{
	win.draw(harbertModeSprite);
}

Sprite & harbertMode_SUPER_DIFFICULT::getSprite() // return sprite data
{
	return harbertModeSprite;
}
