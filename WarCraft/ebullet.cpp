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
	else {
		r++;
		rect.x = start_x + 100 * cos(r);
		rect.y = start_y + 100 * sin(r);
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
	else {
		double a = atan(direct);
		r += speed;
		if (i % 2 == 0) {
			rect.x -= speed*cos(a - 0.017*(i%5));
			rect.y -= speed * sin(a - 0.017*(i%5));
		}
		else {
			rect.x -= speed * cos(a + 0.017*(i%5));
			rect.y -= speed * sin(a + 0.017*(i%5));
		}
	}
}

void ebullet::spfire(double direct)
{
	if (rect.x <= 0 || rect.y <= 60 || rect.y >= SCREEN_HEIGHT - rect.h - 20 || rect.x >= SCREEN_WIDTH - rect.w - 20) {
		isMove = false;
	}
	rect.x += speed;
	rect.y += direct * speed;
}

void ebullet::bouncefire(double direct) {
	if (rect.x >= SCREEN_WIDTH - rect.w - 20) {
		isBouncing1 = true;
		isBouncing2 = false;
		isBouncing3 = false;
		isBouncing4 = false;
	}
	else if (rect.x <= 0) {
		isBouncing2 = true;
		isBouncing1 = false;
		isBouncing3 = false;
		isBouncing4 = false;
	}
	else if (rect.y <= 60) {
		isBouncing3 = true;
		isBouncing1 = false;
		isBouncing2 = false;
		isBouncing4 = false;
	}
	else if (rect.y >= SCREEN_HEIGHT - rect.h - 20) {
		isBouncing4 = true;
		isBouncing1 = false;
		isBouncing2 = false;
		isBouncing3 = false;
	}
}

void ebullet::bounce1(double direct) {
	rect.x -= speed;
	rect.y += direct * speed;
}

void ebullet::bounce2(double direct) {
	rect.x += speed;
	rect.y += direct * speed;
}

void ebullet::bounce3(double direct) {
	rect.y += speed;
	rect.x += direct * speed;
}

void ebullet::bounce4(double direct) {
	rect.y -= speed;
	rect.x += direct * speed;
}