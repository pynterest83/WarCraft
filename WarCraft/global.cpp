#include "global.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;
bool quit = false;
bool Pause = false;
bool Start = true;

Text Score(5, 5, 50, 100, 1);
Text Round(SCREEN_WIDTH / 2 - 175, SCREEN_HEIGHT / 2 - 40, 80, 350, 1);

Mix_Music* cover = NULL;

SDL_Texture* bgr = NULL;
SDL_Texture* scorebar = NULL;
SDL_Texture* explo = NULL;
SDL_Texture* gameover = NULL;
SDL_Texture* life_bar = NULL;
SDL_Texture* energy = NULL;
SDL_Rect scorebar_rect;
SDL_Rect lifebar_rect;
SDL_Rect energy_rect;
SDL_Rect explo_rect;
int score = 0;
int level = 1;
bool check = true;
int cnt = 0;
int curframe_ex = 0;
int curframe_blood = 0;
int curframe_energy = 10;

SDL_Texture* shield_pickup = NULL;
SDL_Texture* shield = NULL;
SDL_Rect shield_rect;
SDL_Rect shieldpickup_rect;
int curframe_shield = 0;
bool isShield = false;
Timer shield_wait;
Timer shield_time;
Timer Shield;
int x_pos, y_pos;

SDL_Texture* f_asteroid = NULL;
SDL_Texture* d_astoroid = NULL;
SDL_Rect f_asteroid_rect;
SDL_Rect d_asteroid_rect;
int curframe_asteroid = 7;
bool isDes = false;
Timer asteroid_wait;
int x_start = SCREEN_WIDTH - 300;
int y_start;
double directA;
double angle = 0;
int wait_time = rand() % 10000 + 5000;

SDL_Texture* heal_pickup = NULL;
SDL_Rect heal_rect;
int curframe_heal = 0;
bool isHeal = false;
Timer heal_wait;
Timer heal_time;
int x_heal, y_heal;
