#pragma once

#include "object.h"
#include "ebullet.h"

class enemy: public object{
private:
    int x;
    int y;
    ebullet shotback;
    bool alive;
    int blood;
public:
    enemy(SDL_Renderer* renderer, int _x, int level);
    ~enemy(){};
    void move(int opt);
    void update(SDL_Renderer* renderer, double direct);
    void autoshot();
    SDL_Rect getRectShotback();
    ebullet& getShotback() { return shotback; };
    void kill(){
        blood--;
        if (blood == 0) {
            alive = false;
            SDL_DestroyTexture(body);
        }
    }; 
    bool is_killed() { return !alive; };
    void setBoss(SDL_Renderer * renderer, int level);
};