#include "ebullet.h"

ebullet::ebullet()
{
	x;
	y;
	isMove = false;
	rect.w = 20;
	rect.h = 20;
}

ebullet::~ebullet()
{
}

void ebullet::fire(double direct, int type)
{

	if (rect.x < 0 || rect.y <0 || rect.y > SCREEN_HEIGHT || rect.x > SCREEN_WIDTH) {
		isMove = false;
	}
	if (type == 2) {
		rect.x -= speed;
		rect.y -= direct * speed;
	}
	else if (type == 1) {
		rect.x -= speed;
	}
}

void ebullet::bossfire(int i, double direct, int type)
{
	if (rect.x < 0 || rect.y <0 || rect.y > SCREEN_HEIGHT || rect.x > SCREEN_WIDTH) {
		isMove = false;
	}
	
	
	if (type == 1) {
		rect.x = rect.x + cos(3.14 / 10 * i) * speed;
		rect.y = rect.y + sin(3.14 / 10 * i) * speed;
	}
	else if (type == 2) {
		rect.x -= speed;
		rect.y -= direct * speed;
	}
}
