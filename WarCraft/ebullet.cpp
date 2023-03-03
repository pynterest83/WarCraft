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

void ebullet::fire(SDL_Rect a, SDL_Rect b)
{
	if (rect.x < 0 || rect.y <0 || rect.y > SCREEN_HEIGHT) {
		isMove = false;
	}
	double direct = (double)(b.y - a.y) / (double)(b.x - a.x);
	if (b.x - a.x < 0) direct = -direct;
	rect.x -= speed;
	rect.y -= direct * speed;
}
