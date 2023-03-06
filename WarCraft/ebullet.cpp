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

void ebullet::fire(double direct)
{
	if (rect.x < 0 || rect.y <0 || rect.y > SCREEN_HEIGHT) {
		isMove = false;
	}
	rect.x -= speed;
	rect.y -= direct * speed;
}
