#include "player.h"

player::player(SDL_Renderer* renderer, int level){
    x = rect.w;
	y = SCREEN_HEIGHT/2;
	rect.w = 60;
	rect.h = 60;
    setPos(x,y);
    shot.setImg(renderer,"resources/playerBullet.png");
	setImg(renderer, "resources/newplayer.png");
	speed = 5 + level;
	blood=50;
	alive=true;
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
			range.push_back(shot);
			for (int i = 0; i < range.size(); i++) {
				if (!range.at(i).is_Move()) {
					range.at(i).setPos(rect.x + rect.w - 8*i, rect.y + rect.h / 2 - range.at(i).getRect().h / 2);
					range.at(i).setStatus(true);
				}
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
		show(renderer, NULL);
		for (int i = 0; i < range.size(); i++) {
			if (range.at(i).is_Move()) {
				range.at(i).fire();
				if (range.at(i).getRect().x >= rect.x + rect.w) range.at(i).show(renderer, NULL);
			}
		}
	}
	else SDL_DestroyTexture(body);
}

SDL_Rect player::getRectBullet()
{
	return shot.getRect();
}