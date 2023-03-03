#include "enemy.h"

enemy::enemy(SDL_Renderer *renderer, int _x, int level){
    alive = true;
    x= _x;
    y= rand()%(SCREEN_HEIGHT-60);
    rect.w = 50;
	rect.h = 50;
    setPos(x,y);
    setImg(renderer, "resources/creep.png");
    shotback.setImg(renderer, "resources/creepbul.png");
    shotback.getSpeed(5 * level);
    blood = 1 * level;
}

void enemy::move(int opt){
    if (rect.y == 0 || rect.y==SCREEN_HEIGHT-rect.h) opt-=1; 
    rect.x-=2;
    if (rect.y < SCREEN_HEIGHT - 3/2*rect.h && opt % 2 == 0) {
        rect.y += 2;
    }
    if (rect.y > 60 + rect.h/2 && opt % 2 != 0) {
        rect.y -= 2;
    }
    if (rect.x<-rect.w) rect.x=SCREEN_WIDTH;
}

void enemy::autoshot(){
    if (!shotback.is_Move() && rect.x<SCREEN_WIDTH){
        shotback.setPos(rect.x, rect.y + rect.h/2 - shotback.getRect().h/2);
        shotback.setStatus(true);
    }
}

void enemy::update(SDL_Renderer* renderer, SDL_Rect a, SDL_Rect b){
    if (alive) {
        show(renderer, NULL);
        if (shotback.is_Move()) {
            shotback.fire(a, b);
            shotback.show(renderer, NULL);
        }
    }
    else SDL_DestroyTexture(body);
}

SDL_Rect enemy::getRectShotback(){
    return shotback.getRect();
}

void enemy::setBoss(SDL_Renderer *renderer, int level) {
    blood = 5*level;
    rect.w = 125;
    rect.h = 100;
    shotback.getsize(50, 50);
    setImg(renderer, "resources/boss.png");
    shotback.setImg(renderer, "resources/bossbul.png");
    shotback.getSpeed(10*level);
    setPos(SCREEN_WIDTH + 200, SCREEN_HEIGHT / 2);
}
