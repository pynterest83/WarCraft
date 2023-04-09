#pragma once

#include "object.h"
#include "bullet.h"
#include "Timer.h"
#include "global.h"
#include "enemy.h"

class player : public object {
private:
	int x;
	int y;
	int w;
	int h;
	bool alive;

	bullet shot[40];
	bullet shottype[2];
	enemy supporter;
	int turn;

	int en_frame;
	SDL_Texture* engine;
	SDL_Texture* engine_boost;

	bool backSpace;
public:
	int blood;
	int num_bullet;
	int damage;
	bool isSkilledQ;
	bool isSkilledR;
	bool SupIsSet;
	int speed;
	bool isP2;
	Timer skill_time;
	Timer skill_wait;

	const Uint8* state = SDL_GetKeyboardState(NULL);
	player();
	void move();
	~player();
	void update(SDL_Renderer* renderer, double direct);
	bullet& getBullet(int i) { return shot[i]; }
	SDL_Rect getRectBullet(int i);
	void kill(int dmg);
	bool isKilled() { return !alive; };
	void handleBullet(SDL_Event event);
	Uint32 getSkillTime() { return skill_wait.GetTime(); }

	void setP2();
	void P2update(SDL_Renderer* renderer);
	void P2HandleBullet(SDL_Event event);

	enemy& getSup() {
		return supporter;
	};
};