#include "game.h"
void game::loadMenu() {
	menu = IMG_LoadTexture(renderer, "resources/menubgr.png");
	start = IMG_LoadTexture(renderer, "resources/start.png");
	game_exit = IMG_LoadTexture(renderer, "resources/exit.png");
	mode1P = IMG_LoadTexture(renderer, "resources/pve.png");
	mode2P = IMG_LoadTexture(renderer, "resources/pvp.png");
	back = IMG_LoadTexture(renderer, "resources/back.png");
	pauseheader = IMG_LoadTexture(renderer, "resources/pauseheader.png");
	pausewindow = IMG_LoadTexture(renderer, "resources/pausewindow.png");
	replay = IMG_LoadTexture(renderer, "resources/replay.png");
	game_quit = IMG_LoadTexture(renderer, "resources/gamequit.png");
	game_continue = IMG_LoadTexture(renderer, "resources/continue.png");
	record = IMG_LoadTexture(renderer, "resources/highscore.png");
	rec_but = IMG_LoadTexture(renderer, "resources/window.png");
	rec_header = IMG_LoadTexture(renderer, "resources/recordheader.png");
	start_rect = { SCREEN_WIDTH/2 - 125, 250, 250, 80 };
	rec_but_rect = { SCREEN_WIDTH / 2 - 125, 350, 250, 80 };
	rec_header_rect = { SCREEN_WIDTH / 2 - 100, 370, 200, 40 };
	exit_rect = { SCREEN_WIDTH/2 - 125, 450, 250, 80 };
	mode1P_rect = { SCREEN_WIDTH / 2 - 250 - 50, SCREEN_HEIGHT / 2 - 40, 250, 80 };
	mode2P_rect = { SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 40, 250, 80 };
	back_rect = { 10, 10 , 50, 50 };
	pauseheader_rect = { SCREEN_WIDTH / 2 - 150, 110, 300, 50 };
	pausewindow_rect = { SCREEN_WIDTH / 2 - 200, 100, 400, 500 };
	replay_rect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50, 100, 100 };
	game_quit_rect = { SCREEN_WIDTH / 2 - 50 + 110, SCREEN_HEIGHT / 2 - 50, 100, 100 };
	game_continue_rect = { SCREEN_WIDTH / 2 - 50 - 110, SCREEN_HEIGHT / 2 - 50, 100, 100 };
}
void game :: loadSound() {
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	cover = Mix_LoadMUS("sound/Levels-Avicii.mp3");
	p_shot1 = Mix_LoadWAV("sound/p_shot1.ogg");
	p_shot2 = Mix_LoadWAV("sound/p_shot2.wav");
	explo_sound = Mix_LoadWAV("sound/explo_sound.ogg");
	asteroid = Mix_LoadWAV("sound/asteroid.wav");
	shield_hit = Mix_LoadWAV("sound/shield_hit.wav");
	picked = Mix_LoadWAV("sound/picked.wav");
	skillE = Mix_LoadWAV("sound/skillE.wav");
	skillQ = Mix_LoadWAV("sound/skillQ.wav");
	Mix_PlayMusic(cover, -1);
	Mix_VolumeMusic(30);
	Mix_VolumeChunk(explo_sound, 30);
	Mix_VolumeChunk(p_shot1, 50);
	Mix_VolumeChunk(p_shot2, 50);
}

void game :: loadDefault() {
	bgr = IMG_LoadTexture(renderer, "resources/bgr.png");
	scorebar = IMG_LoadTexture(renderer, "resources/scorebar.png");
	explo = IMG_LoadTexture(renderer, "resources/explosion2.png");
	gameover = IMG_LoadTexture(renderer, "resources/gameover.png");
	life_bar = IMG_LoadTexture(renderer, "resources/lifebar.png");
	energy = IMG_LoadTexture(renderer, "resources/energy.png");
	scorebar_rect = { 0, 0, SCREEN_WIDTH, 60 };
	lifebar_rect = { 200, 0, 140, 60 };
	energy_rect = { 160, 0, 40, 60 };
	explo_rect;
}

void game::loadShield (){
		shield_pickup = IMG_LoadTexture(renderer, "resources/shield_pickup.png");
		shield = IMG_LoadTexture(renderer, "resources/Shield.png");
		shield_rect;
		shieldpickup_rect;
}

void game::loadAsteroid() {
	f_asteroid = IMG_LoadTexture(renderer, "resources/asteroid_fly.png");
	d_astoroid = IMG_LoadTexture(renderer, "resources/asteroid_destroy.png");
	f_asteroid_rect;
	d_asteroid_rect;
}

void game::loadHeal() {
	heal_pickup = IMG_LoadTexture(renderer, "resources/heal_pickup.png");
	heal_rect;
}

void game::Resetgame() {
	score = 0;
	level = 1;
	check = true;
	cnt = 0;
	curframe_ex = 0;
	curframe_blood = 0;
	curframe_energy = 10;
	explo_rect = { 0, 0, 0, 0 };

	curframe_shield = 0;
	isShield = false;
	shield_wait.Reset();
	shield_time.Reset();
	Shield.Reset();
	shieldpickup_rect = { 0,0,0,0 };
	shield_rect = { 0,0,0, 0};

	curframe_asteroid = 7;
	isDes = false;
	asteroid_wait.Reset();
	x_start = SCREEN_WIDTH - 300;
	angle = 0;
	wait_time = rand() % 10000 + 5000;
	d_asteroid_rect = { 0, 0, 0, 0 };
	f_asteroid_rect = { 0, 0, 0, 0 };

	curframe_heal = 0;
	isHeal = false;
	heal_wait.Reset();
	heal_time.Reset();
	heal_rect = { 0, 0, 0, 0 };
	
	SDL_RenderClear(renderer);
}

