#include "game.h"

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
		shield_wait.Start();
}

void game::loadAsteroid() {
	f_asteroid = IMG_LoadTexture(renderer, "resources/asteroid_fly.png");
	d_astoroid = IMG_LoadTexture(renderer, "resources/asteroid_destroy.png");
	f_asteroid_rect;
	d_asteroid_rect;
	asteroid_wait.Start();
}

void game::loadHeal() {
	heal_pickup = IMG_LoadTexture(renderer, "resources/heal_pickup.png");
	heal_rect;
	heal_wait.Start();
}

