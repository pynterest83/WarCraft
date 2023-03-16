#pragma once

#include "object.h"
#include "ebullet.h"

class enemy: public object{
private:
    int x;
    int y;
    ebullet shotback;
    ebullet bossshot[20];

    bool alive;
    int blood;
    
    int e_frame;
    SDL_Texture* engine;
    SDL_Rect e_des;
public:
    bool isBoss = false;
    bool bossMove = false;
    int typeshot;

    enemy(SDL_Renderer* renderer, int _x, int level);
    ~enemy(){};

    void move(int opt, int y_pos);

    void update(SDL_Renderer* renderer, double direct);

    void autoshot();
    void bossautoshot();

    SDL_Rect getRectShotback();
    ebullet& getShotback() { return shotback; };
    ebullet& getbossShot(int i) { return bossshot[i]; };

    void kill(int dmg){
        blood-=dmg;
        if (blood <= 0) {
            alive = false;
            SDL_DestroyTexture(body);
        }
    }; 
    bool is_killed() { return !alive; };

    void setBoss(SDL_Renderer * renderer, int level);
};