#pragma once

#include "object.h"
#include "bullet.h"

class player : public object {
private:
	int x;
	int y;
	int w;
	int h;
	int speed;
	bool alive;

	bullet shot;
	
	int en_frame;
	SDL_Texture* engine;
	SDL_Texture* engine_boost;

	SDL_Texture* p_status[3];
public:
	int blood;
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