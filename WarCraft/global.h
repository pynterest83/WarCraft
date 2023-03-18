#pragma once

#include "rendergame.h"
#include "player.h"
#include "bullet.h"
#include "object.h"
#include "enemy.h"
#include "Text.h"
#include "ebullet.h"
#include <vector>
#include <string>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <fstream>
#include "Timer.h"

using namespace RD;
using namespace std;

//default feature
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Event event;
extern SDL_Point mouse;
extern bool quit;
extern bool Pause;
extern bool Start;
extern bool isChoose;
extern int gametype;
extern fstream highscore;

extern Text Score;
extern Text Round;

extern Mix_Music* cover;

extern SDL_Texture* menu;
extern SDL_Texture* game_exit;
extern SDL_Texture* start;
extern SDL_Texture* mode1P;
extern SDL_Texture* mode2P;
extern SDL_Texture* back;
extern SDL_Rect exit_rect;
extern SDL_Rect start_rect;
extern SDL_Rect mode1P_rect;
extern SDL_Rect mode2P_rect;
extern SDL_Rect back_rect;

extern SDL_Texture* bgr;
extern SDL_Texture* scorebar;
extern SDL_Texture* explo;
extern SDL_Texture* gameover;
extern SDL_Texture* life_bar;
extern SDL_Texture* energy;
extern SDL_Rect scorebar_rect;
extern SDL_Rect lifebar_rect;
extern SDL_Rect energy_rect;
extern SDL_Rect explo_rect;
extern int score;
extern int level;
extern bool check;
extern int cnt;
extern int curframe_ex;
extern int curframe_blood;
extern int curframe_energy;

extern SDL_Texture* shield_pickup;
extern SDL_Texture* shield;
extern SDL_Rect shield_rect;
extern SDL_Rect shieldpickup_rect;
extern int curframe_shield;
extern bool isShield;
extern Timer shield_wait;
extern Timer shield_time;
extern Timer Shield;
extern int x_pos, y_pos;

extern SDL_Texture* f_asteroid;
extern SDL_Texture* d_astoroid;
extern SDL_Rect f_asteroid_rect;
extern SDL_Rect d_asteroid_rect;
extern int curframe_asteroid;
extern bool isDes;
extern Timer asteroid_wait;
extern int x_start;
extern int y_start;
extern double directA;
extern double angle;
extern int wait_time;

extern SDL_Texture* heal_pickup;
extern SDL_Rect heal_rect;
extern int curframe_heal;
extern bool isHeal;
extern Timer heal_wait;
extern Timer heal_time;
extern int x_heal, y_heal;