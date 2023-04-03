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

	Text rate(SCREEN_WIDTH /2 - 150, SCREEN_HEIGHT/2 - 40, 50, 300, 1);
	rate.initText(font_text, "font/Koulen-Regular.ttf");

	while (!quit) {
		while (!Start && !quit && !isChoose && !isHi && !isInf && !isSet && !isShop) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			renderMenu();
		}
		while (Start && !quit && !isChoose) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			renderMenu2();
		}
		while (isHi && !quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			renderMenuHighScore();
			for (int i = 0; i < 10; i++) {
				rate.setPos(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 200 + i * 50);
				rate.setText("TOP   " + to_string(i+1) + "         " + to_string(rating[i]));
				rate.createaText(font_text, renderer);
			}

			SDL_RenderPresent(renderer);
		}
		while (isInf && !quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			renderMenuInfo();
		}
		while (isShop && !quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
			}
			renderMenuShop();
		}
		while (isSet && !quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}

				if (event.type == SDL_DROPFILE) {
					char* dropped_filedir = event.drop.file;
					const char* path = dropped_filedir;
					cover = Mix_LoadMUS(path);
					Mix_PlayMusic(cover, -1);
					SDL_free(dropped_filedir);
				}
			}
			renderMenuSettings();
		}
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
				Game.loadSingleGame(astro1, list_creep, Boss);
			}
			else if (gametype == 2) {
				player astro2;
				astro2.setP2();
				astro2.isP2 = true;
				Game.load2Playergame(astro1, astro2);
			}
		}
	}

	//quit sdl
	RD::quitSDL(window, renderer);
	return 0;
}