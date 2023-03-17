#pragma once

#include "object.h"
#include "bullet.h"
#include "Timer.h"

class player : public object {
private:
	int x;
	int y;
	int w;
	int h;
	bool alive;

	bullet shot[40];
	bullet shottype[2];
	int turn;
	Timer skill_time;
	Timer skill_wait;

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
	int speed;
	bool isP2;

	const Uint8* state = SDL_GetKeyboardState(NULL);
	player(SDL_Renderer* renderer);
	void move();
	~player();
	void update(SDL_Renderer* renderer);
	bullet& getBullet(int i) { return shot[i]; }
	SDL_Rect getRectBullet(int i);
	void kill(int dmg);
	bool isKilled() { return !alive; };
	void handleBullet(SDL_Event event);
	Uint32 getSkillTime() { return skill_wait.GetTime(); }

	void setP2(SDL_Renderer* renderer);
	void P2update(SDL_Renderer* renderer);
	void P2HandleBullet(SDL_Event event);
};