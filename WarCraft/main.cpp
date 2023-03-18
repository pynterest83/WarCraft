#include "game.h"

game Game;
int main(int argc, char* argv[]) {
	//init random
	srand((unsigned int)time(NULL)); 

	//init SDL
	initSDL(window, renderer);

	//load and setup some feature
	Game.loadText();
	Game.loadSound();
	Game.loadDefault();
	Game.loadShield();
	Game.loadAsteroid();
	Game.loadHeal();
	Game.loadMenu();

	while (!quit && !isChoose) {
		while (!Start) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			renderMenu();
		}
		while (Start) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			renderMenu2();
		}
	}

	//initialize player and enemy
	player astro1(renderer);
	if (gametype == 1) {
		vector<enemy> list_creep;
		for (int i = 0; i < 5; i++) {
			enemy sEnemy(renderer, SCREEN_WIDTH + i * 200, level);
			list_creep.push_back(sEnemy);
		}
		// Set Boss
		enemy Boss(renderer, SCREEN_WIDTH + 200, level);
		Boss.setBoss(renderer, level);
		Boss.bossautoshot();
		Game.loadSingleGame(astro1, list_creep, Boss);
	}
	else if (gametype == 2) {
		player astro2(renderer);
		astro2.setP2(renderer);
		astro2.isP2 = true;
		Game.load2Playergame(astro1, astro2);
	}

	//quit sdl
	RD::quitSDL(window, renderer);
	return 0;
}