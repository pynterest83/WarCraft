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
	if (rect.x < 0 || rect.y <0 || rect.y > SCREEN_HEIGHT || rect.x > SCREEN_WIDTH) {
		isMove = false;
	}
	rect.x -= speed;
	rect.y -= direct * speed;
}

void ebullet::bossfire(int i)
{
	if (rect.x < 0 || rect.y <0 || rect.y > SCREEN_HEIGHT) {
		isMove = false;
	}
	rect.x = rect.x + cos(3.14 / 10 * i) * speed;
	rect.y = rect.y + sin(3.14 / 10 * i) * speed;
}
