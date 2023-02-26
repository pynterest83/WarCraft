#include "bossBullet.h"
#include "object.h"

bossBullet::bossBullet()
{
	x;
	y;
	isMove = false;
	speed = 20;
	rect.w = 30;
	rect.h = 30;
}

bossBullet::~bossBullet()
{
}

void bossBullet::fire(SDL_Rect a, SDL_Rect b)
{
	if (rect.x < 0 || rect.y < 0) {
		isMove = false;
	}
	float direct = (float)(b.y - a.y) / (float)(b.x - a.x);
	rect.x -= speed;
	rect.y -= direct * speed;
}