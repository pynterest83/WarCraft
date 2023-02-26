#include "creep.h"

creep::creep(SDL_Renderer *renderer, int _x){
    alive=true;
    x= _x;
    y= rand()%(SCREEN_HEIGHT-60);
    rect.w = 50;
	rect.h = 50;
    setPos(x,y);
    setImg(renderer, "creep.png");
    shotback.setImg(renderer, "creepbul.png");
}

void creep::move(int opt){
    if (rect.y == 0 || rect.y==SCREEN_HEIGHT-rect.h) opt-=1; 
    rect.x-=2;
    if (rect.y < SCREEN_HEIGHT - rect.h && opt % 2 == 0) {
        rect.y += 2;
    }
    if (rect.y > 60 && opt % 2 != 0) {
        rect.y -= 2;
    }
    if (rect.x<-rect.w) rect.x=SCREEN_WIDTH;
}

void creep::autoshot(){
    if (!shotback.is_Move() && rect.x<SCREEN_WIDTH){
        shotback.setPos(rect.x, rect.y + rect.h/2 - shotback.getRect().h/2);
        shotback.setStatus(true);
    }
}

void creep::update(SDL_Renderer* renderer, SDL_Rect a, SDL_Rect b){
    if (alive) {
        show(renderer);

        if (shotback.is_Move()) {
            shotback.fire(a, b);
            shotback.show(renderer);
        }
    }
    else SDL_DestroyTexture(body);
}

SDL_Rect creep::getRectShotback(){
    return shotback.getRect();
}

