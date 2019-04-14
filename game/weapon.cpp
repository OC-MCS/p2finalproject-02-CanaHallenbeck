#include "weapon.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;


shot::shot(Vector2f pos, attackType b_OR_m)
{
	xPos = pos.x;
	yPos = pos.y;
	bombOrMissile = b_OR_m;
}

missile::missile(Vector2f pos, Texture & t) : shot(pos, MISSILE)
{
	missileSprite.setPosition(pos);
	missileSprite.setTexture(t);
}

void missile::draw(RenderWindow & win)
{
	win.draw(missileSprite);
}

 Sprite & missile::getSprite()
{
	return missileSprite;
}

 bomb::bomb(Vector2f pos, Texture & t) : shot(pos, BOMB)
 {
	 bombSprite.setPosition(pos);
	 bombSprite.setTexture(t);
 }

 void bomb::draw(RenderWindow & win)
 {
	 win.draw(bombSprite);
 }

 Sprite & bomb::getSprite()
 {
	 return bombSprite;
 }
