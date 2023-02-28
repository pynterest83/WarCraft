#include "player.h"

player::player(SDL_Renderer* renderer){
    x = rect.w;
	y = SCREEN_HEIGHT/2;
	rect.w = 50;
	rect.h = 50;
    setPos(x,y);
    shot.setImg(renderer,"playerBullet.png");
	setImg(renderer, "player.png");
    speed=10;
	blood=40;
	alive=true;
}

void player::move(){
	const Uint8 *state = SDL_GetKeyboardState(NULL);
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
			shot.setPos(rect.x+rect.w, rect.y + rect.h/2 - shot.getRect().h/2);
			shot.setStatus(true);
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
		show(renderer);

		if (shot.is_Move()) {
			shot.fire();
			shot.show(renderer);
		}
	}
}

SDL_Rect player::getRectBullet()
{
	return shot.getRect();
}