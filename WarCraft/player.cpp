#include "player.h"

player::player(SDL_Renderer* renderer){
    x = rect.w;
	y = SCREEN_HEIGHT/2;
	rect.w = 60;
	rect.h = 60;
    setPos(x,y);
    shot.setImg(renderer,"E:/personal/Code/C++/LTNC/GameSDL2/WarCraft/WarCraft/playerBullet.png");
    speed=10;
	blood=40;
	alive=true;
}

void player::move(SDL_Event e){
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (rect.x<SCREEN_WIDTH-rect.w && state[SDL_SCANCODE_D]) rect.x+=speed;
	if (rect.x-speed>0 && state[SDL_SCANCODE_A]) rect.x-=speed;
	if (rect.y-speed>0 && state[SDL_SCANCODE_W]) rect.y-=speed;
	if (rect.y<SCREEN_HEIGHT-rect.h && state[SDL_SCANCODE_S]) rect.y+=speed;

	if (e.type == SDL_MOUSEBUTTONDOWN) {
		if (!shot.is_Move()) {
			shot.setPos(rect.x+rect.w/2, rect.y + rect.h/2 - shot.getRect().h/2);
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
			setImg(renderer, "E:/personal/Code/C++/LTNC/GameSDL2/WarCraft/WarCraft/playershot.png");
			shot.fire();
			shot.show(renderer);
		}

		if (!shot.is_Move()){
			setImg(renderer,"E:/personal/Code/C++/LTNC/GameSDL2/WarCraft/WarCraft/player.png");
		}
	}
}

SDL_Rect player::getRectBullet()
{
	return shot.getRect();
}