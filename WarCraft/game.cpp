#include "game.h"
void game::loadMenu() {
	menu = IMG_LoadTexture(renderer, "resources/menubgr.png");
	start = IMG_LoadTexture(renderer, "resources/start.png");
	game_exit = IMG_LoadTexture(renderer, "resources/exit.png");
	mode1P = IMG_LoadTexture(renderer, "resources/pve.png");
	mode2P = IMG_LoadTexture(renderer, "resources/pvp.png");
	back = IMG_LoadTexture(renderer, "resources/back.png");
	pause = IMG_LoadTexture(renderer, "resources/pause.png");
	pauseheader = IMG_LoadTexture(renderer, "resources/pauseheader.png");
	pausewindow = IMG_LoadTexture(renderer, "resources/pausewindow.png");
	replay = IMG_LoadTexture(renderer, "resources/replay.png");
	game_quit = IMG_LoadTexture(renderer, "resources/gamequit.png");
	game_continue = IMG_LoadTexture(renderer, "resources/continue.png");
	record = IMG_LoadTexture(renderer, "resources/highscore.png");
	rec_but = IMG_LoadTexture(renderer, "resources/window.png");
	rec_header = IMG_LoadTexture(renderer, "resources/recordheader.png");
	inf_but = IMG_LoadTexture(renderer, "resources/window.png");
	info_header = IMG_LoadTexture(renderer, "resources/infoheader.png");
	info = IMG_LoadTexture(renderer, "resources/information.jpg");
	sound[0] = IMG_LoadTexture(renderer, "resources/sound1.png");
	sound[1] = IMG_LoadTexture(renderer, "resources/sound2.png");
	SOUND = sound[0];
	settings = IMG_LoadTexture(renderer, "resources/settings.png");
	set_but = IMG_LoadTexture(renderer, "resources/set_but.png");

	start_rect = { SCREEN_WIDTH/2 - 125, 250, 250, 80 };
	rec_but_rect = { SCREEN_WIDTH / 2 - 125, 350, 250, 80 };
	rec_header_rect = { SCREEN_WIDTH / 2 - 100, 370, 200, 40 };
	inf_but_rect = { SCREEN_WIDTH / 2 - 125, 450, 250, 80 };
	inf_header_rect = { SCREEN_WIDTH / 2 - 100, 470, 200, 40 };
	exit_rect = { SCREEN_WIDTH/2 - 125, 550, 250, 80 };
	mode1P_rect = { SCREEN_WIDTH / 2 - 250 - 50, SCREEN_HEIGHT / 2 - 40, 250, 80 };
	mode2P_rect = { SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 40, 250, 80 };
	back_rect = { 10, 10 , 50, 50 };
	pauseheader_rect = { SCREEN_WIDTH / 2 - 150, 110, 300, 50 };
	pausewindow_rect = { SCREEN_WIDTH / 2 - 200, 100, 400, 500 };
	replay_rect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50, 100, 100 };
	game_quit_rect = { SCREEN_WIDTH / 2 - 50 + 110, SCREEN_HEIGHT / 2 - 50, 100, 100 };
	game_continue_rect = { SCREEN_WIDTH / 2 - 50 - 110, SCREEN_HEIGHT / 2 - 50, 100, 100 };
	pause_rect = { SCREEN_WIDTH - 120, 5, 50, 50 };
	sound_rect = { SCREEN_WIDTH - 60, 5, 50, 50 };
	set_but_rect = { 10, SCREEN_HEIGHT - 70, 50, 50 };
}
void game :: loadSound() {
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	cover = Mix_LoadMUS("sound/Levels-Avicii.mp3");
	p_shot1 = Mix_LoadWAV("sound/p_shot1.ogg");
	chunk[0] = p_shot1;
	p_shot2 = Mix_LoadWAV("sound/p_shot2.wav");
	chunk[1] = p_shot2;
	explo_sound = Mix_LoadWAV("sound/explo_sound.ogg");
	chunk[2] = explo_sound;
	asteroid = Mix_LoadWAV("sound/asteroid.wav");
	chunk[3] = asteroid;
	shield_hit = Mix_LoadWAV("sound/shield_hit.wav");
	chunk[4] = shield_hit;
	picked = Mix_LoadWAV("sound/picked.wav");
	chunk[5] = picked;
	skillE = Mix_LoadWAV("sound/skillE.wav");
	chunk[6] = skillE;
	skillQ = Mix_LoadWAV("sound/skillQ.wav");
	chunk[7] = skillQ;
	Mix_PlayMusic(cover, -1);
	Mix_VolumeMusic(30);
	Mix_VolumeChunk(explo_sound, 30);
	Mix_VolumeChunk(p_shot1, 50);
	Mix_VolumeChunk(p_shot2, 50);
}

void game :: loadDefault() {
	type = rand() % 2 + 1;
	for (int i = 0; i < 2; i++) {
		bgr[i] = loadTexture(renderer, "resources/bgr" + to_string(i + 1) + ".png");
	}
	stars = IMG_LoadTexture(renderer, "resources/stars.png");
	scorebar = IMG_LoadTexture(renderer, "resources/scorebar.png");
	explo = IMG_LoadTexture(renderer, "resources/explosion2.png");
	gameover = IMG_LoadTexture(renderer, "resources/gameover.png");
	life_bar = IMG_LoadTexture(renderer, "resources/lifebar.png");
	energy = IMG_LoadTexture(renderer, "resources/energy.png");
	scorebar_rect = { 0, 0, SCREEN_WIDTH, 60 };
	lifebar_rect = { 200, 0, 140, 60 };
	energy_rect = { 160, 0, 40, 60 };
	bgr_rect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
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

	highscore.close();
	
	SDL_RenderClear(renderer);
}

void game::loadCharacter() {
	for (int i = 0; i < 2; i++) {
		creep[i] = loadTexture(renderer, "resources/creep" + to_string(i+1) + ".png");
		boss[i] = loadTexture(renderer, "resources/boss" + to_string(i+1) + ".png");
		creep_bul[i] = loadTexture(renderer, "resources/creepbul" + to_string(i+1) + ".png");
		boss_bul[i] = loadTexture(renderer, "resources/bossbul" + to_string(i+1) + ".png");
		p_shot[i] = loadTexture(renderer, "resources/playerbullet" + to_string(i + 1) + ".png");
		e_flame[i] = loadTexture(renderer, "resources/e_flame" + to_string(i + 1) + ".png");
	}

	for (int i = 0; i < 3; i++) {
		p_img[i] = loadTexture(renderer, "resources/player" + to_string(i + 1) + ".png");
	}
	p_engine = loadTexture(renderer, "resources/engine_boost.png");
	p_sup = loadTexture(renderer, "resources/support1.png");
	p_sup_bul = loadTexture(renderer, "resources/supportbul1.png");
	mouse_img = loadTexture(renderer, "resources/setCursor.png");
}

