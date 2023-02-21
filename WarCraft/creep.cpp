#include "creep.h"

creep::creep(SDL_Renderer *renderer, int _x){
    alive=true;
    x= _x;
    y= rand()%SCREEN_HEIGHT;
    rect.w = 60;
	rect.h = 60;
    setPos(x,y);
    setImg(renderer, "E:/personal/Code/C++/LTNC/GameSDL2/WarCraft/WarCraft/creep.png");
    shotback.setImg(renderer, "E:/personal/Code/C++/LTNC/GameSDL2/WarCraft/WarCraft/creepbul.png");
}

void creep::move(int opt){
    if (rect.y==rect.h/2 || rect.y==SCREEN_HEIGHT-rect.h/2) opt-=1; 
    rect.x-=2;
    if (rect.y<SCREEN_HEIGHT-rect.h && opt%2==0) rect.y+=2;
    if (rect.y>0 && opt%2!=0) rect.y-=2;
    if (rect.x<-rect.w) rect.x=SCREEN_WIDTH;
}

void creep::autoshot(){
    if (!shotback.is_Move() && rect.x<SCREEN_WIDTH){
        shotback.setPos(rect.x-rect.w/2, rect.y + rect.h/2 - shotback.getRect().h/2);
        shotback.setStatus(true);
    }
}

void creep::update(SDL_Renderer* renderer){
    if (alive){
        show(renderer);

        if (shotback.is_Move()) {
			shotback.fire();
			shotback.show(renderer);
		}
    }
}

SDL_Rect creep::getRectShotback(){
    return shotback.getRect();
}