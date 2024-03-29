#include "game.h"

game Game;
int main(int argc, char* argv[]) {
	//init random
	srand((unsigned int)time(NULL)); 

	//init SDL
	initSDL(window, renderer);

	//load and setup some feature
	Game.loadCharacter();
	Game.loadText();
	Game.loadSound();
	Game.loadDefault();
	Game.loadShield();
	Game.loadAsteroid();
	Game.loadHeal();
	Game.loadMenu();

	while (!quit) {
		// render menu
		while (!Start && !quit && !isChoose && !isHi && !isInf && !isSet && !isShop) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			renderMenu();
		}

		// render choose gametype menu
		while (Start && !quit && !isChoose) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			Game.Resetgame();
			renderMenu2();
		}

		// render high score menu
		while (isHi && !quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			renderMenuHighScore();
		}

		// render info menu
		while (isInf && !quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			renderMenuInfo();
		}

		// render shop menu
		while (isShop && !quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			renderMenuShop();
		}

		// render setting menu
		while (isSet && !quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}

				// change background music
				if (event.type == SDL_DROPFILE) {
					// get the file path
					char* dropped_filedir = event.drop.file;
					const char* path = dropped_filedir;
					cover = Mix_LoadMUS(path);
					Mix_PlayMusic(cover, -1);
					SDL_free(dropped_filedir);
				}
			}
			renderMenuSettings();
		}

		// render gameplay
		while (isChoose && !quit) {
			Pause = false;
			Game.Resetgame();
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			player astro1;
			//initialize player and enemy
			if (gametype == 1) {
				vector<enemy> list_creep;
				for (int i = 0; i < 5; i++) {
					enemy sEnemy(SCREEN_WIDTH + i * 200, level);
					sEnemy.setImg(creep[type - 1][i%5]);
					list_creep.push_back(sEnemy);
				}
				enemy Boss(SCREEN_WIDTH + 200, level);
				Boss.setBoss(level);
				Boss.bossautoshot();

				// load single game
				Game.loadSingleGame(astro1, list_creep, Boss);
			}
			else if (gametype == 2) {
				player astro2;
				astro2.setP2();
				astro2.isP2 = true;

				// load 2 player game
				Game.load2Playergame(astro1, astro2);
			}
		}
	}

	//quit sdl
	RD::quitSDL(window, renderer);
	return 0;
}