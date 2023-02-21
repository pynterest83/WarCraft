#pragma once

#include "object.h"
#include "ebullet.h"

class creep: public object{
private:
    int x;
    int y;
    ebullet shotback;
    bool alive;
public:
    creep(SDL_Renderer* renderer, int _x);
    ~creep(){};
    void move(int opt);
    void update(SDL_Renderer* renderer);
    void autoshot();
    SDL_Rect getRectShotback();
    void kill(){ alive = false;};
    bool is_killed() { return !alive; };
};