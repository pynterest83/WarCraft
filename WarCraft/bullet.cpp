#include "bullet.h"

bullet::bullet()
{
	x;
	y;
	isMove = false;
	speed = 30;
	rect.w = 25;
	rect.h = 15;
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
	
}