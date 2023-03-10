#include "player.h"

player::player(SDL_Renderer* renderer, int level){
    x = rect.w;
	y = SCREEN_HEIGHT/2;
	rect.w = 60;
	rect.h = 60;
    setPos(x,y);
    shot.setImg(renderer,"resources/playerBullet.png");
	speed = 5 + level;
	blood=50;
	alive=true;

	engine = IMG_LoadTexture(renderer, "resources/engine.png");
	engine_boost = IMG_LoadTexture(renderer, "resources/engine_boost.png");
	en_frame = 0;

	p_status[0] = IMG_LoadTexture(renderer, "resources/player1.png");
	p_status[1] = IMG_LoadTexture(renderer, "resources/player2.png");
	p_status[2] = IMG_LoadTexture(renderer, "resources/player3.png");
}

void player::move(){
	if (alive) {
		if (rect.x < SCREEN_WIDTH - rect.w && (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])) {
			rect.x += speed;
		}
		if (rect.x - speed > 0 && (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])) {
			rect.x -= speed;
		}
		if (rect.y - speed > 60 && (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])) {
			rect.y -= speed;
		}
		if (rect.y < SCREEN_HEIGHT - rect.h && (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])) {
			rect.y += speed;
		}

		if (state[SDL_SCANCODE_SPACE]) {
			if (!shot.is_Move()) {
				shot.setPos(rect.x + rect.w, rect.y + rect.h / 2 - shot.getRect().h / 2);
				shot.setStatus(true);
			}
		}
	}
}

player::~player(){

}

void player::kill(){
	blood--;
	if (blood==0){
		alive=false;
	}
}

void player::update(SDL_Renderer* renderer)
{
	if (alive)
	{
		if (blood >= 35) body = p_status[0];
		else if (blood >= 10) body = p_status[1];
		else body = p_status[2];
		show(renderer, NULL);

		SDL_Rect e_boost = { rect.x - 30, rect.y - 20, 100, 100 };
		SDL_Rect e_source = { 0, en_frame*48, 48, 48 };
		SDL_Rect e_des = { rect.x - 55, rect.y - 22, 200 ,100 };
		SDL_RenderCopy(renderer, engine_boost, NULL, &e_boost);
		SDL_RenderCopy(renderer, engine, &e_source, &e_des);
		en_frame++;
		en_frame = en_frame % 7;

		if (shot.is_Move()) {
			shot.fire();
			shot.show(renderer, NULL);
		}
	}
	else SDL_DestroyTexture(body);
}

SDL_Rect player::getRectBullet()
{
	return shot.getRect();
}