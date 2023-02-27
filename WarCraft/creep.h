#pragma once

#include "object.h"
#include "ebullet.h"

class creep: public object{
private:
    int x;
    int y;
    ebullet shotback;
    bool alive;
    int blood;
public:
    creep(SDL_Renderer* renderer, int _x);
    ~creep(){};
    void move(int opt);
    void update(SDL_Renderer* renderer, SDL_Rect a, SDL_Rect b);
    void autoshot();
    SDL_Rect getRectShotback();
    ebullet& getShotback() { return shotback; };
    void kill(){
        blood--;
        if (blood == 0) alive = false;
    }; 
    bool is_killed() { return !alive; };
    void setBoss(SDL_Renderer * renderer);
};