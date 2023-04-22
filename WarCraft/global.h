#pragma once

#include "Text.h"
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

// EXTERN ALL FEATURE IN GLOBAL.CPP

//default feature
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Event event;
extern SDL_Point mouse;
extern bool quit;
extern bool Pause;
extern bool Start;
extern bool isChoose;
extern bool isHi;
extern bool isInf;
extern bool isSet;
extern bool isMute;
extern bool isShop;
extern bool isBought[2];
extern bool isFullScreen;
extern int gametype;
extern int type;
extern int player_skin;
extern fstream highscore;
extern fstream money;
extern fstream bought;
extern vector<int> rating;

extern Text Score;
extern Text Round;
extern Text GameOver1;
extern Text GameOver2;
extern Text Money;
extern Text DisPlayFps;
extern Text rate;
extern Text money_sum;

extern Mix_Music* cover;
extern Mix_Chunk* p_shot1;
extern Mix_Chunk* skillE;
extern Mix_Chunk* skillQ;
extern Mix_Chunk* p_shot2;
extern Mix_Chunk* explo_sound;
extern Mix_Chunk* shield_hit;
extern Mix_Chunk* picked;
extern Mix_Chunk* asteroid;
extern Mix_Chunk* chunk[];

extern SDL_Texture* menu;
extern SDL_Texture* game_exit;
extern SDL_Texture* start;
extern SDL_Texture* mode1P;
extern SDL_Texture* mode2P;
extern SDL_Texture* back;
extern SDL_Texture* pause;
extern SDL_Texture* sound[];
extern SDL_Texture* SOUND;
extern SDL_Texture* pauseheader;
extern SDL_Texture* pausewindow;
extern SDL_Texture* replay;
extern SDL_Texture* game_quit;
extern SDL_Texture* game_continue;
extern SDL_Texture* record;
extern SDL_Texture* rec_but;
extern SDL_Texture* rec_header;
extern SDL_Texture* info;
extern SDL_Texture* info_header;
extern SDL_Texture* inf_but;
extern SDL_Texture* settings;
extern SDL_Texture* zoom;
extern SDL_Texture* set_but;
extern SDL_Texture* slider1;
extern SDL_Texture* slider2;
extern SDL_Texture* gfx;
extern SDL_Texture* sfx;
extern SDL_Texture* border;
extern SDL_Texture* shop_but;
extern SDL_Texture* shopbgr;
extern SDL_Texture* coin;
extern SDL_Texture* price[2];
extern SDL_Rect price_rect[2];
extern SDL_Rect coin_rect1;
extern SDL_Rect coin_rect2;
extern SDL_Rect shop_window_rect;
extern SDL_Rect shop_item[3];
extern SDL_Rect rec_header_rect;
extern SDL_Rect rec_but_rect;
extern SDL_Rect inf_header_rect;
extern SDL_Rect inf_but_rect;
extern SDL_Rect exit_rect;
extern SDL_Rect start_rect;
extern SDL_Rect mode1P_rect;
extern SDL_Rect mode2P_rect;
extern SDL_Rect back_rect;
extern SDL_Rect pauseheader_rect;
extern SDL_Rect pausewindow_rect;
extern SDL_Rect replay_rect;
extern SDL_Rect game_quit_rect;
extern SDL_Rect game_continue_rect;
extern SDL_Rect sound_rect;
extern SDL_Rect pause_rect;
extern SDL_Rect set_but_rect;
extern SDL_Rect gfx_control;
extern SDL_Rect sfx_control;
extern SDL_Rect gfx_rect;
extern SDL_Rect sfx_rect;
extern SDL_Rect setting_rect;
extern SDL_Rect border_rect1;
extern SDL_Rect border_rect2;
extern SDL_Rect shop_but_rect;

extern SDL_Texture* bgr[];
extern SDL_Texture* scorebar;
extern SDL_Texture* explo;
extern SDL_Texture* gameover;
extern SDL_Texture* life_bar;
extern SDL_Texture* energy;
extern SDL_Rect scorebar_rect;
extern SDL_Rect lifebar_rect;
extern SDL_Rect energy_rect;
extern SDL_Rect explo_rect;
extern SDL_Rect bgr_rect;
extern int score;
extern int coin_cnt;
extern int coin_sum;
extern int level;
extern bool check;
extern int cnt;
extern int curframe_ex;
extern int curframe_blood;
extern int curframe_energy;
extern Timer frame;

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

extern SDL_Texture* creep[3][5];
extern SDL_Texture* boss[3][2];
extern SDL_Texture* creep_bul[];
extern SDL_Texture* boss_bul[];
extern SDL_Texture* p_img[];
extern SDL_Texture* p_shot[];
extern SDL_Texture* e_flame[];
extern SDL_Texture* p_sup;
extern SDL_Texture* p_sup_bul;
extern SDL_Texture* p_engine;
extern SDL_Texture* mouse_img;
extern SDL_Texture* new_player[2];
extern SDL_Texture* new_player_bul[2];