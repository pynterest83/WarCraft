#include "game.h"
void game::loadMenu() {
	menu = IMG_LoadTexture(renderer, "resources/menubgr.png");
	start = IMG_LoadTexture(renderer, "resources/start.png");
	game_exit = IMG_LoadTexture(renderer, "resources/exit.png");
	mode1P = IMG_LoadTexture(renderer, "resources/pve.png");
	mode2P = IMG_LoadTexture(renderer, "resources/pvp.png");
	back = IMG_LoadTexture(renderer, "resources/back.png");
	start_rect = { SCREEN_WIDTH/2 - 125, 250, 250, 80 };
	exit_rect = { SCREEN_WIDTH/2 - 125, 350, 250, 80 };
	mode1P_rect = { SCREEN_WIDTH / 2 - 250 - 50, SCREEN_HEIGHT / 2 - 40, 250, 80 };
	mode2P_rect = { SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 40, 250, 80 };
	back_rect = { 10, 10 , 50, 50 };
}
void game :: loadSound() {
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	cover = Mix_LoadMUS("resources/Levels-Avicii.mp3");
	Mix_PlayMusic(cover, -1);
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

