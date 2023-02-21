#pragma once

#include "object.h"
#include "bossBullet.h"

class boss : public object {
private:
    int blood;
    int x;
    int y;
    int w;
    int h;
    bossBullet bossShot;
    bool alive;
public:
    boss(SDL_Renderer* renderer);
    ~boss(){};
    void move();
    void update(SDL_Renderer* renderer);
    SDL_Rect getbossBullet();
    void kill();
    bool isKilled(return !alive);
}