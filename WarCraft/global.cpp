#include "global.h"

// The window we'll be rendering to
SDL_Window* window = NULL;
// global renderer, event and mouse
SDL_Renderer* renderer = NULL;
SDL_Event event;
SDL_Point mouse;

// gametype
int gametype;
// enemy or round type
int type;
// player skin/ shop
int player_skin = 1;

// flags
bool quit = false; // total game quit
bool Pause = false; // game pause
bool Start = false; // game start
bool isChoose = false; // choose mode menu
bool isHi = false; // highscore menu
bool isInf = false; // gameinfo menu
bool isSet = false; // settings menu
bool isMute = false; // mute
bool isShop = false; // shop menu
bool isBought[2]; // check if item is bought
bool isFullScreen = false;// fullscreen mode

// game database
fstream highscore;
fstream money;
fstream bought;
vector<int> rating;

// game text
Text Score(5, 5, 50, 100, 1);
Text Round(SCREEN_WIDTH / 2 - 175, SCREEN_HEIGHT / 2 - 40, 80, 350, 1);
Text GameOver1(SCREEN_WIDTH / 2 - 175, SCREEN_HEIGHT / 2 - 100, 80, 350, 1);
Text GameOver2(SCREEN_WIDTH / 2 - 175, SCREEN_HEIGHT / 2 - 100, 80, 350, 1);
Text Money(SCREEN_WIDTH/2 + 400, 5, 50, 20, 1);
Text DisPlayFps(SCREEN_WIDTH / 2 - 25, 5, 50, 50, 1);
Text rate(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 40, 50, 300, 1);
Text money_sum(SCREEN_WIDTH / 2 - 70, 60, 60, 60, 1);

// game sound
Mix_Music* cover = NULL; // music cover
Mix_Chunk* p_shot1 = NULL; // player shottype 1
Mix_Chunk* skillE = NULL; // player skill E
Mix_Chunk* skillQ = NULL; // player skill Q
Mix_Chunk* p_shot2 = NULL; // player shottype 2
Mix_Chunk* explo_sound = NULL; // explosion sound
Mix_Chunk* shield_hit = NULL; // shield hit sound
Mix_Chunk* picked = NULL; // pickup shield or heal sound
Mix_Chunk* asteroid = NULL; // asteroid flying sound
Mix_Chunk* chunk[8]; // all sound chunk

// All menu texture

// main menu
SDL_Texture* menu = NULL; // game menu background
SDL_Texture* game_exit = NULL; // exit button
SDL_Texture* start = NULL; // game start button
SDL_Texture* back = NULL; // back button
SDL_Rect exit_rect;
SDL_Rect start_rect;
SDL_Rect back_rect;

// game mode menu
SDL_Texture* mode1P = NULL; // game mode 1 player button
SDL_Texture* mode2P = NULL; // game mode 2 player button
SDL_Rect mode1P_rect;
SDL_Rect mode2P_rect;

// in game menu
SDL_Texture* pause = NULL; // pause button
SDL_Texture* sound[2]; // sound mute/unmuted button
SDL_Texture* SOUND; // selection mute/unmuted button
SDL_Rect pause_rect;
SDL_Rect sound_rect;

// pause menu
SDL_Texture* pauseheader = NULL; // pause window header
SDL_Texture* pausewindow = NULL; // pause window
SDL_Texture* replay = NULL; // replay button
SDL_Texture* game_quit = NULL; // quit button
SDL_Texture* game_continue = NULL; // continue button
SDL_Rect pauseheader_rect;
SDL_Rect pausewindow_rect;
SDL_Rect replay_rect;
SDL_Rect game_quit_rect;
SDL_Rect game_continue_rect;

// highscore menu
SDL_Texture* record = NULL; // highscore background
SDL_Texture* rec_but = NULL; // highscore button
SDL_Texture* rec_header = NULL; // highscore header
SDL_Rect rec_header_rect;
SDL_Rect rec_but_rect;

// gameinfo menu
SDL_Texture* info_header = NULL; // gameinfo header
SDL_Texture* inf_but = NULL; // gameinfo button
SDL_Texture* info = NULL; // gameinfo background
SDL_Rect inf_header_rect;
SDL_Rect inf_but_rect;

// settings menu
SDL_Texture* settings = NULL; // settings background
SDL_Texture* zoom = NULL; // fullscreen button
SDL_Texture* set_but = NULL; // settings button
SDL_Texture* slider1 = NULL; // slider of gfx button
SDL_Texture* slider2 = NULL; // slider of sfx button
SDL_Texture* gfx = NULL; // music header 
SDL_Texture* sfx = NULL; // sound header
SDL_Texture* border = NULL; // border of slider
SDL_Rect set_but_rect;
SDL_Rect gfx_control;
SDL_Rect sfx_control;
SDL_Rect gfx_rect;
SDL_Rect sfx_rect;
SDL_Rect setting_rect;
SDL_Rect border_rect1;
SDL_Rect border_rect2;

// shop menu
SDL_Texture* shop_but = NULL; // shop button
SDL_Texture* shopbgr = NULL; // shop background
SDL_Texture* coin = NULL; // coin texture
SDL_Texture* price[2]; // price of item
SDL_Rect price_rect[2];
SDL_Rect coin_rect1;
SDL_Rect coin_rect2;
SDL_Rect shop_window_rect;
SDL_Rect shop_item[3];
SDL_Rect shop_but_rect;

// All ingame texture/feature
SDL_Texture* bgr[3];
SDL_Texture* scorebar = NULL;
SDL_Texture* explo = NULL;
SDL_Texture* gameover = NULL;
SDL_Texture* life_bar = NULL;
SDL_Texture* energy = NULL;
SDL_Rect scorebar_rect;
SDL_Rect lifebar_rect;
SDL_Rect energy_rect;
SDL_Rect explo_rect;
SDL_Rect bgr_rect;
int score = 0;
int coin_cnt = 0;
int coin_sum;
int level = 1;
bool check = true;
int cnt = 0;
int curframe_ex = 0;
int curframe_blood = 0;
int curframe_energy = 10;
Timer frame;

// Picked up item texture

// shield
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

// asteroid
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

// heal
SDL_Texture* heal_pickup = NULL;
SDL_Rect heal_rect;
int curframe_heal = 0;
bool isHeal = false;
Timer heal_wait;
Timer heal_time;
int x_heal, y_heal;

// All player/enemy texture
SDL_Texture* creep[3][5];
SDL_Texture* boss[3][2];
SDL_Texture* creep_bul[3];
SDL_Texture* boss_bul[3];
SDL_Texture* p_img[3];
SDL_Texture* p_shot[2];
SDL_Texture* e_flame[2];
SDL_Texture* p_sup;
SDL_Texture* p_sup_bul;
SDL_Texture* p_engine;
SDL_Texture* mouse_img; // mouse cursor for skillR
SDL_Texture* new_player[2];
SDL_Texture* new_player_bul[2];