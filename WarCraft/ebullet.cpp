#include "ebullet.h"

ebullet::ebullet()
{
	x;
	y;
	isMove = false;
	speed = 30;
	rect.w = 20;
	rect.h = 10;
}

ebullet::~ebullet()
{
}

void ebullet::fire()
{
	if (rect.x < 0) {
		isMove = false;
	}
	rect.x -= speed;
}
