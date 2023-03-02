#pragma once

#include "object.h"
#include "bullet.h"

class player : public object {
private:
	int x;
	int y;
	int w;
	int h;
	bullet shot;
	int blood;
	int speed;
	bool alive;
public:
	player(SDL_Renderer* renderer, int level);
	void move();
	~player();
	void update(SDL_Renderer* renderer);
	SDL_Rect getRectBullet();
	bullet& getBullet() { return shot; }
	void kill();
	bool isKilled(){ return !alive;};
};