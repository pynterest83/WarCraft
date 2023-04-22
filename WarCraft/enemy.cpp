#include "enemy.h"

enemy::enemy(int _x, int level){
    // reset enemy
    SDL_Texture* new_body = NULL;
    body = new_body;
    setImg(creep[type - 1][rand()%5]);
    SDL_DestroyTexture(new_body);

    // set enemy
    alive = true;
    x= _x;
    y= rand()%(SCREEN_HEIGHT) + 60;
    rect.w = 50;
	rect.h = 50;
    setPos(x,y);
    blood = 1 * level;
    // set enemy bullet
    shotback.setImg(creep_bul[type-1]);
    shotback.getSpeed(5 * level);

    // set enemy engine
    engine = e_flame[0];
    e_frame = 0;
}

void enemy::move(int opt, int y_pos, double direct) {
    // creep move
    if (!isBoss) {
        // type 1,2 enemy fly and shoot
        if (type == 1 || type == 2) {
            if (rect.y == 0 || rect.y == SCREEN_HEIGHT - rect.h) opt -= 1;
            rect.x -= 2;
            if (rect.y < SCREEN_HEIGHT - 3 / 2 * rect.h && opt % 2 == 0) {
                rect.y += 2;
            }
            if (rect.y > 60 + rect.h / 2 && opt % 2 != 0) {
                rect.y -= 2;
            }
            if (rect.x < -rect.w) rect.x = SCREEN_WIDTH;
        }
        // type 3: enemy direct fly to player
        else {
            rect.x -= 5;
            if (direct>=-sqrt(3) && direct <= sqrt(3)) rect.y -= direct * 5;
        }
    }

    // boss move
    else {
        // boss AI
        // move out of screen
		if (rect.x > SCREEN_WIDTH - rect.h - 50) rect.x -= 2;
        else {
            // if boss see player, boss move to avoid player
			if (rect.y >= y_pos - 15 && rect.y <= y_pos + 15) bossMove = true;
            // move down/up
            if (bossMove) {
				if (rect.y < y_pos) rect.y -= 2;
				if (rect.y > y_pos) rect.y += 2;
				if (rect.y == SCREEN_HEIGHT / 4 || rect.y == SCREEN_HEIGHT * 3 / 4) bossMove = false;
			}
            // if not see, still moving
            if (!bossMove) {
				if (rect.y < y_pos) rect.y += 2;
				if (rect.y > y_pos) rect.y -= 2;
				if (rect.y == SCREEN_HEIGHT / 4 || rect.y == SCREEN_HEIGHT * 3 / 4) bossMove = true;
			}
		}
    }
}

void enemy::autoshot(){
    // type 1,2 enemy shoot, bullet plying
    if (type == 1 || type == 2) {
        if (!shotback.is_Move() && rect.x < SCREEN_WIDTH) {
            shotback.setPos(rect.x, rect.y + rect.h / 2 - shotback.getRect().h / 2);
            shotback.setStatus(true);
        }
    }
    else {
        // set the circle center to move the bullet around
        shotback.start_x = rect.x;
        shotback.start_y = rect.y + rect.h / 2 - shotback.getRect().h / 2;
        if (!shotback.is_Move() && rect.x < SCREEN_WIDTH) {
            shotback.setPos(rect.x - 100, rect.y + rect.h / 2 - shotback.getRect().h / 2);
            shotback.setStatus(true);
        }
    }
}

void enemy::spautoshot() {
    // set all support bullet not to bounce
    for (int i = 0; i < 20; i++) {
        spshot[i].isBouncing1 = false;
        spshot[i].isBouncing2 = false;
        spshot[i].isBouncing3 = false;
        spshot[i].isBouncing4 = false;
    }
    // ready to shoot
    for (int i = 0; i < 20; i++) {
        if (!spshot[i].is_Move()) {
            spshot[i].setPos(rect.x + rect.w, rect.y + rect.h / 2 - bossshot[i].getRect().h / 2);
            spshot[i].setStatus(true);
        }
    }
}

void enemy::bossautoshot() {
    // set all boss bullet ready to shoot and set the circle center to move the bullet around and set the radius = 0
    for (int i = 0; i < 20; i++) {
        if (!bossshot[i].is_Move() && rect.x < SCREEN_WIDTH) {
			bossshot[i].setPos(rect.x, rect.y + rect.h / 2 - bossshot[i].getRect().h / 2);
			bossshot[i].setStatus(true);
            bossshot[i].start_x = rect.x;
            bossshot[i].start_y = rect.y + rect.h/2 - bossshot[i].getRect().h/2;
            bossshot[i].r = 0;
		}
	}
}

void enemy::update(SDL_Renderer* renderer, double direct){
    if (alive) {
        show(renderer, NULL);

        // set engine animation
        // set enemy engine source frame
        SDL_Rect e_source = { 0, e_frame * 128, 128, 128 };
        
        // set enemy engine for boss
        if (isBoss) {
            e_des = {rect.x - 85, rect.y - 25, 250, 150};
        }
        // set enemy engine for other enemy
        else e_des = { rect.x - 120, rect.y - 25, 200 ,100 };
        SDL_RenderCopy(renderer, engine, &e_source, &e_des);
        e_frame++;
        e_frame = e_frame % 8;

        if (!isBoss) {
            // update creep
            if (!isSp) {
                if (shotback.is_Move()) {
                    shotback.fire(direct, type);
                    shotback.show(renderer, NULL);
                }
            }
            // support update
            else {
                // avoid accessing out of array
                spshot[0].setStatus(false);
                // the previous bullet is not moving, the next bullet is ready to shoot
                for (int i = 1; i < 20; i++) {
                    if (spshot[i].is_Move() && !spshot[i - 1].is_Move()) {
                        if (-sqrt(3) <= direct && direct <= sqrt(3)) spshot[i].spfire(direct);
                        spshot[i].show(renderer, NULL);
                    }
                    // if the previous bullet is not moving, start bouncing and detect which direction to bounce
                    if (!spshot[i-1].is_Move()) {
                        spshot[i-1].bouncefire(direct);
                    }
                    // if bouncing from the left side
                    if (spshot[i - 1].isBouncing1) {
                        spshot[i - 1].bounce1(direct);
                        spshot[i - 1].show(renderer, NULL);
                    }
                    // if bouncing from the right side
                    if (spshot[i - 1].isBouncing2) {
                        spshot[i - 1].bounce2(direct);
                        spshot[i - 1].show(renderer, NULL);
					}
                    // if bouncing from the top side
                    if (spshot[i - 1].isBouncing3) {
                        spshot[i - 1].bounce3(direct);
                        spshot[i - 1].show(renderer, NULL);
                    }
                    // if bouncing from the bottom side
                    if (spshot[i - 1].isBouncing4) {
                        spshot[i - 1].bounce4(direct);
                        spshot[i - 1].show(renderer, NULL);
                    }
                }
            }
        }
        else {
            if (type == 1 || type == 3 ) {
                for (int i = 0; i < 20; i++) {
                    if (bossshot[i].is_Move()) {
                        bossshot[i].bossfire(i, direct, type);
                        bossshot[i].show(renderer, NULL);
                    }
                }
            }
            else if (type == 2) {
                // avoid accessing out of array
                bossshot[0].setStatus(false);
                // the previous bullet is not moving, the next bullet is ready to shoot
                for (int i = 1; i < 20; i++) {
                    if (bossshot[i].is_Move() && !bossshot[i-1].is_Move()) {
                        bossshot[i].bossfire(i, direct, type);
                        bossshot[i].show(renderer, NULL);
                    }
                }
            }
        }
    }
    else SDL_DestroyTexture(body);
}

// get rect of enemy bullet to check interaction
SDL_Rect enemy::getRectShotback(){
    return shotback.getRect();
}

// set boss feature
void enemy::setBoss(int level) {
    blood = 5*level;
    rect.w = 125;
    rect.h = 100;
    setImg(boss[type - 1][level%2]);
    setPos(SCREEN_WIDTH + 200, SCREEN_HEIGHT / 2);

    shotback.getsize(35, 35);
    shotback.setImg(boss_bul[type-1]);
    shotback.getSpeed(10+level);
    for (int i = 0; i < 20; i++) {
        bossshot[i] = shotback;
    }
}

// set support feature
void enemy::setSp() {
    rect.w = 40;
    rect.h = 40;
    setImg(p_sup);

    alive = true;
    isSp = true;

    shotback.getsize(20, 20);
    shotback.setImg(p_sup_bul);
    shotback.getSpeed(5);

    for (int i = 0; i < 20; i++) {
        spshot[i] = shotback;
    }
}