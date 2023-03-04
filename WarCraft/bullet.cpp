#include "bullet.h"

bullet::bullet()
{
	x;
	y;
	isMove = false;
	speed = 30;
	rect.w = 20;
	rect.h = 10;
}

bullet::~bullet()
{
}

void bullet::fire()
{
	if (isMove) {
		if (rect.x > SCREEN_WIDTH) {
			isMove = false;
		}
		rect.x += speed;
	}
	else SDL_DestroyTexture(body);
	
}