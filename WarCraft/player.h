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

	bullet shot[40];
	bullet shottype[2];
	int turn;

	int en_frame;
	SDL_Texture* engine;
	SDL_Texture* engine_boost;

	SDL_Texture* p_status[3];
	bool backSpace;
public:
	int blood;
	int num_bullet;
	int damage;
	bool isSkilled;

	const Uint8* state = SDL_GetKeyboardState(NULL);
	player(SDL_Renderer* renderer, int level);
	void move();
	~player();
	void update(SDL_Renderer* renderer);
	bullet& getBullet(int i) { return shot[i]; }
	SDL_Rect getRectBullet(int i);
	void kill();
	bool isKilled() { return !alive; };
	void handleBullet(SDL_Event event);
};