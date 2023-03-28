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
		r += speed;
		rect.x = start_x + r*cos(3.14 / 10 * i);
		rect.y = start_y + r*sin(3.14 / 10 * i);
	}
	else if (type == 2) {
		rect.x -= speed;
		rect.y -= direct * speed;
	}
}

void ebullet::spfire(double direct)
{
	if (rect.x < 0 || rect.y <0 || rect.y > SCREEN_HEIGHT || rect.x > SCREEN_WIDTH) {
		isMove = false;
	}
	rect.x += speed;
	rect.y += direct * speed;
}
