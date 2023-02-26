#include "boss.h"

boss::boss(SDL_Renderer* renderer) {
	x = SCREEN_WIDTH /2;
	y = SCREEN_HEIGHT / 2;
	w = 200;
	h = 200;
	setPos(x, y);
	setImg(renderer, "boss.png");
	bossShot.setImg(renderer, "bossbul.png");
	blood = 100;
	alive = true;
}

void boss::move() {
	rect.x-=2;
	if (rect.x<-rect.w) rect.x=SCREEN_WIDTH;
}

void boss::autoshot() {
	if (!bossShot.is_Move() && rect.x < SCREEN_WIDTH) {
		bossShot.setPos(rect.x, rect.y + rect.h / 2 - bossShot.getRect().h / 2);
		bossShot.setStatus(true);
	}
}

void boss::update(SDL_Renderer* renderer, SDL_Rect a, SDL_Rect b) {
	if (alive) {
		show(renderer);
		if (bossShot.is_Move()) {
			bossShot.fire(a, b);
			bossShot.show(renderer);
		}
	}
	else SDL_DestroyTexture(body);
}

SDL_Rect boss::getRectbossBullet() {
	return bossShot.getRect();
}

void boss::kill() {
	blood--;
	if (blood == 0) {
		alive = false;
	}
}