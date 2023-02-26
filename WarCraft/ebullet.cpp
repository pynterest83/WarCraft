#include "ebullet.h"

ebullet::ebullet()
{
	x;
	y;
	isMove = false;
	speed = 5;
	rect.w = 20;
	rect.h = 20;
}

ebullet::~ebullet()
{
}

void ebullet::fire(SDL_Rect a, SDL_Rect b)
{
	if (rect.x < 0 || rect.y <0 || rect.y > SCREEN_HEIGHT) {
		isMove = false;
	}
	float direct = (float)(b.y - a.y) / (float)(b.x - a.x);
	rect.x -= speed;
	rect.y -= direct * speed;
}
