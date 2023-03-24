#include "bullet.h"

bullet::bullet()
{
	x;
	y;
	isMove = false;
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
	else setPos(0, 0);
	
}

void bullet::p2fire() {
	if (isMove) {
		if (rect.x < 0) {
			isMove = false;
		}
		rect.x -= speed;
	}
	else setPos(0, 0);
}