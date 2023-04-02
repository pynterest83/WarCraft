#pragma once

#include "object.h"
#include "ebullet.h"
#include "global.h"

class enemy: public object{
private:
    int x;
    int y;
    ebullet shotback;
    ebullet bossshot[20];
    ebullet spshot[20];

    bool alive;
    int blood;
    
    int e_frame;
    SDL_Texture* engine;
    SDL_Rect e_des;
public:
    bool isBoss = false;
    bool bossMove = false;
    bool isSp = false;

    enemy(int _x, int level);
    enemy() {};
    ~enemy(){};

    void move(int opt, int y_pos, double direct);

    void update(SDL_Renderer* renderer, double direct);

    void autoshot();
    void bossautoshot();
    void spautoshot();

    SDL_Rect getRectShotback();
    ebullet& getShotback() { return shotback; };
    ebullet& getbossShot(int i) { return bossshot[i]; };
    ebullet& getspShot(int i) { return spshot[i]; };

    void kill(int dmg){
        blood-=dmg;
        if (blood <= 0) {
            alive = false;
        }
    }; 
    bool is_killed() { return !alive; };

    void setBoss(int level);
    void setSp();
};