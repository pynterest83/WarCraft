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
	const Uint8* state = SDL_GetKeyboardState(NULL);
	player(SDL_Renderer* renderer, int level);
	void move();
	~player();
	void update(SDL_Renderer* renderer);
	bullet& getBullet() { return shot; }
	SDL_Rect getRectBullet();
	void kill();
	bool isKilled(){ return !alive;};
};