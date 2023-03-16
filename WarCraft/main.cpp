#include "rendergame.h"
#include "player.h"
#include "bullet.h"
#include "object.h"
#include "enemy.h"
#include "text.h"
#include "ebullet.h"
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

//using namespace rendergame
using namespace RD;
using namespace std;

int main(int argc, char* argv[]) {
	//init random
	srand((unsigned int)time(NULL));

	//default feature
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;
	bool quit = false;

	//init SDL
	initSDL(window, renderer);

	// initialize text
	Text Score(5, 5, 50, 100, 1);
	Score.initText(font_text, "font/Koulen-Regular.ttf");
	Text Round(SCREEN_WIDTH / 2 - 175, SCREEN_HEIGHT / 2 - 40, 80, 350, 1);
	Round.initText(font_text, "font/Koulen-Regular.ttf");

	//initSound
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	Mix_Music* cover = Mix_LoadMUS("resources/Levels-Avicii.mp3");
	Mix_PlayMusic(cover, -1);

	//load and setup some feature
	SDL_Texture* bgr = IMG_LoadTexture(renderer, "resources/bgr.png");
	SDL_Texture* scorebar = IMG_LoadTexture(renderer, "resources/scorebar.png");
	SDL_Texture* explo = IMG_LoadTexture(renderer, "resources/explosion2.png");
	SDL_Texture* gameover = IMG_LoadTexture(renderer, "resources/gameover.png");
	SDL_Texture* shield_pickup = IMG_LoadTexture(renderer, "resources/shield_pickup.png");
	SDL_Texture* shield = IMG_LoadTexture(renderer, "resources/Shield.png");
	SDL_Texture* life_bar = IMG_LoadTexture(renderer, "resources/lifebar.png");
	SDL_Texture* energy = IMG_LoadTexture(renderer, "resources/energy.png");
	SDL_Texture* f_asteroid = IMG_LoadTexture(renderer, "resources/asteroid_fly.png");
	SDL_Texture* d_astoroid = IMG_LoadTexture(renderer, "resources/asteroid_destroy.png");
	SDL_Texture* heal_pickup = IMG_LoadTexture(renderer, "resources/heal_pickup.png");

	SDL_Rect scorebar_rect = { 0, 0, SCREEN_WIDTH, 60 };
	SDL_Rect lifebar_rect = { 200, 0, 140, 60 };
	SDL_Rect energy_rect = { 160, 0, 40, 60 };
	SDL_Rect explo_rect;
	SDL_Rect shield_rect;
	SDL_Rect shieldpickup_rect;
	SDL_Rect f_asteroid_rect;
	SDL_Rect d_asteroid_rect;
	SDL_Rect heal_rect;

	//default feature
	int score = 0;
	int level = 1;
	bool check = true;
	int cnt = 0;
	ifstream f;
	int curframe_ex = 0;
	int curframe_shield = 0;
	int curframe_blood = 0;
	int curframe_energy = 10;
	int curframe_asteroid = 7;
	int curframe_heal = 0;

	// set Shield
	bool isShield = false;
	Timer shield_wait;
	shield_wait.Start();
	Timer shield_time;
	Timer Shield;
	int x_pos, y_pos;

	// set Asteroid
	bool isDes = false;
	Timer asteroid_wait;
	asteroid_wait.Start();
	int x_start = SCREEN_WIDTH - 300;
	int y_start;
	double directA;
	double angle = 0;
	int wait_time = rand() % 10000 + 5000;

	// set Heal
	bool isHeal = false;
	Timer heal_wait;
	heal_wait.Start();
	Timer heal_time;
	int x_heal, y_heal;

	//initialize player and enemy
	player astro(renderer, level);
	vector<enemy> list_creep;
	for (int i = 0; i < 5; i++) {
		enemy sEnemy(renderer, SCREEN_WIDTH + i * 200, level);
		list_creep.push_back(sEnemy);
	}

	// Set Boss
	enemy Boss(renderer, SCREEN_WIDTH + 200, level);
	Boss.setBoss(renderer, level);
	Boss.bossautoshot();

	//main loop
	while (!quit && !astro.isKilled()) {
		//event loop
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			astro.handleBullet(event);
		}
		//render background
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bgr, NULL, NULL);
		SDL_RenderCopy(renderer, scorebar, NULL, &scorebar_rect);

		// astro move
		astro.move();
		int dmg = astro.damage;

		// set up shield
		if (!isShield) {
			if (shield_wait.GetTime() > (Uint32)10000) {
				if (!shield_wait.Paused) shield_time.Start();
				shield_wait.Pause();
				shieldpickup_rect = { x_pos, y_pos, 50, 50 };
				if (checkCollision(shieldpickup_rect, astro.getRect())) {
					shield_wait.Reset();
					isShield = true;
					Shield.Start();
				}
				if (shield_time.GetTime() > (Uint32)10000) {
					shield_wait.Reset();
					shield_wait.Unpause();
					shield_wait.Start();
					shield_time.Reset();
				}
			}
			else {
				x_pos = rand() % 600;
				y_pos = rand() % 600;
				if (y_pos <= 60) y_pos += 100;
			}
		}

		if (isShield)
		{
			shield_rect = { astro.getRect().x - 30, astro.getRect().y - 20, 100, 100 };
			SDL_RenderCopy(renderer, shield, NULL, &shield_rect);
			if (Shield.GetTime() > (Uint32)(12000)) {
				isShield = false;
				shield_wait.Unpause();
				shield_wait.Start();
			}
		}

		// set up heal
		if (!isHeal) {
			if (heal_wait.GetTime() > (Uint32)10000 && astro.blood < 20) {
				if (!heal_wait.Paused) heal_time.Start();
				heal_wait.Pause();
				heal_rect = { x_heal, y_heal, 50, 50 };
				if (checkCollision(heal_rect, astro.getRect())) {
					heal_wait.Reset();
					isHeal = true;
				}
				if (heal_time.GetTime() > (Uint32)10000) {
					heal_wait.Reset();
					heal_wait.Unpause();
					heal_wait.Start();
					heal_time.Reset();
				}
			}
			else {
				x_heal = rand() % 600;
				y_heal = rand() % 600;
				if (y_heal <= 60) y_heal += 100;
			}
		}

		if (isHeal) {
			astro.blood += 10;
			isHeal = false;
			heal_wait.Unpause();
			heal_wait.Start();
		}

		// setup asteroid
		if (!isDes) {
			if (asteroid_wait.GetTime() > (Uint32)wait_time) {
				asteroid_wait.Pause();
				f_asteroid_rect.x -= 15;
				f_asteroid_rect.y -= directA * 15;
				angle -= 30;
				SDL_RenderCopyEx(renderer, f_asteroid, NULL, &f_asteroid_rect, angle, NULL, SDL_FLIP_NONE);
				if (checkCollision(f_asteroid_rect, astro.getRect())) {
					isDes = true;
					if (!isShield) {
						curframe_ex = 0;
						explo_rect = { astro.getRect().x + 10, astro.getRect().y + 10, 75, 75 };

						astro.kill();
					}
				}
				if (f_asteroid_rect.x <= 0 || f_asteroid_rect.y >= SCREEN_HEIGHT || f_asteroid_rect.y <= 0) {
					isDes = true;
				}
			}
			else {
				y_start = rand() % 600 + 60;
				f_asteroid_rect = { x_start, y_start, 96, 96 };
				directA = (double)(astro.getRect().y - f_asteroid_rect.y) / (astro.getRect().x - f_asteroid_rect.x);
			}
		}

		else {
			d_asteroid_rect = { f_asteroid_rect.x - 20, f_asteroid_rect.y - 20 , 150, 150 };
			curframe_asteroid = 7;

			isDes = false;
			asteroid_wait.Reset();
			asteroid_wait.Start();
			wait_time = rand() % 10000 + 5000;
		}

		//check shooting
		for (int i = 0; i < 5; i++) {
			if (!list_creep.at(i).is_killed()) {
				//check astro bullet - enemy
				if (list_creep.at(i).getRect().x + list_creep.at(i).getRect().w < SCREEN_WIDTH) {
					for (int j = 0; j < astro.num_bullet; j++) {
						if (checkCollision(astro.getRectBullet(j), list_creep.at(i).getRect()) && astro.getBullet(j).is_Move()) {
							list_creep.at(i).kill(dmg);
							if (list_creep.at(i).is_killed()) {
								curframe_ex = 0;
								explo_rect = { list_creep.at(i).getRect().x - 50, list_creep.at(i).getRect().y - 50, 200, 200 };
								enemy sEnemy(renderer, SCREEN_WIDTH + i * 200, level);
								list_creep.at(i) = sEnemy;
								score += 10 + (level - 1) * 2;
								cnt++;
							}

							else {
								curframe_ex = 0;
								explo_rect = { list_creep.at(i).getRect().x, list_creep.at(i).getRect().y, 50, 50 };
							}
							astro.getBullet(j).setStatus(false);
						}
					}
				}

				//check astro - enemy bullet
				if (checkCollision(astro.getRect(), list_creep.at(i).getRectShotback())) {
					if (!isShield) {
						curframe_ex = 0;
						explo_rect = { astro.getRect().x + 10, astro.getRect().y + 10, 50, 50 };

						astro.kill();
					}
					list_creep.at(i).getShotback().setStatus(false);
				}

				//check astro - enemy 
				if (checkCrash(astro.getRect(), list_creep.at(i).getRect())) {
					curframe_ex = 0;
					explo_rect = { list_creep.at(i).getRect().x - 50, list_creep.at(i).getRect().y - 50, 200, 200 };

					if (!isShield) astro.kill();
					list_creep.at(i).kill(level + 1);
					enemy sEnemy(renderer, SCREEN_WIDTH + i * 200, level);
					list_creep.at(i) = sEnemy;
					score += 10 + (level - 1) * 2;
					cnt++;
				}

				// enemy move and update enemy
				int opt = rand() % 10000;
				list_creep.at(i).move(opt, astro.getRect().y);
				double direct = (double)(astro.getRect().y - list_creep.at(i).getRect().y) / (astro.getRect().x - list_creep.at(i).getRect().x);
				list_creep.at(i).update(renderer, direct);
				if (-sqrt(3) <= direct && direct <= sqrt(3)) list_creep.at(i).autoshot();
			}
		}

		// generate boss
		if (cnt == 15) {
			check = true;
			Boss.isBoss = true;
		}
		if (score >= 150 && check) {
			double direct = (double)(astro.getRect().y - Boss.getRect().y) / (astro.getRect().x - Boss.getRect().x);
			Boss.update(renderer, direct);
			//if (-1 <= direct && direct <= 1) 
			Boss.bossautoshot();
			int opt = rand() % 10000;
			Boss.move(opt, astro.getRect().y);

			for (int j = 0; j < astro.num_bullet; j++) {
				if (checkCollision(astro.getRectBullet(j), Boss.getRect()) && astro.getBullet(j).is_Move() && Boss.getRect().x + Boss.getRect().w < SCREEN_WIDTH) {
					curframe_ex = 0;
					explo_rect = { astro.getRectBullet(j).x - 10, astro.getRectBullet(j).y - 10, 100, 100 };

					Boss.kill(dmg);
					astro.getBullet(j).setStatus(false);
				}
			}

			for (int i = 0; i < 20; i++) {
				if (checkCollision(astro.getRect(), Boss.getbossShot(i).getRect())) {
					if (!isShield) {
						curframe_ex = 0;
						explo_rect = { astro.getRect().x - 25, astro.getRect().y - 25, 100, 100 };

						for (int i = 0; i < level; i++) {
							astro.kill();
						}
					}
					Boss.getShotback().setStatus(false);
				}
			}

			if (checkCrash(astro.getRect(), Boss.getRect())) {
				curframe_ex = 0;
				explo_rect = { Boss.getRect().x, Boss.getRect().y, 100, 100 };
				if (!isShield) {
					for (int i = 0; i < level; i++) {
						astro.kill();
					}
				}
				Boss.kill(level + 1);
			}

			if (Boss.is_killed() && check) {
				Boss.isBoss = false;
				curframe_ex = 0;
				explo_rect = { Boss.getRect().x - Boss.getRect().w, Boss.getRect().y - Boss.getRect().h, 300, 300 };
				while (curframe_ex < 70) {
					SDL_Rect source_rect = { curframe_ex * 100, 0, 100, 100 };
					SDL_RenderClear(renderer);
					SDL_RenderCopy(renderer, bgr, NULL, NULL);
					SDL_RenderCopy(renderer, scorebar, NULL, &scorebar_rect);
					SDL_RenderCopy(renderer, explo, &source_rect, &explo_rect);
					Score.setText("Score: " + to_string(score));
					Score.createaText(font_text, renderer);
					SDL_RenderPresent(renderer);
					curframe_ex++;
				}

				// regenBoss and Enemy
				enemy Boss1(renderer, SCREEN_WIDTH - 100, level);
				Boss1.setBoss(renderer, level);
				check = false;
				score += 50 * level;
				cnt = 0;
				Boss = Boss1;

				for (int i = 0; i < astro.num_bullet; i++) {
					astro.getBullet(i).setStatus(false);
				}
				for (int i = 0; i < 5; i++) {
					list_creep.at(i).kill(level + 1);
					enemy sEnemy(renderer, SCREEN_WIDTH + i * 200, level);
					list_creep.at(i) = sEnemy;
				}

				// update level
				level++;
				SDL_SetTextureAlphaMod(bgr, 150);
				SDL_RenderCopy(renderer, scorebar, NULL, &scorebar_rect);
				SDL_RenderCopy(renderer, bgr, NULL, NULL);
				Score.setText("Score: " + to_string(score));
				Score.createaText(font_text, renderer);
				Round.setText("ROUND " + to_string(level));
				Round.createaText(font_text, renderer);
				SDL_RenderPresent(renderer);
				SDL_Delay(3000);
			}
		}

		//render and update astro by time
		astro.update(renderer);
		if (astro.isKilled()) {
			curframe_ex = 0;
			explo_rect = { astro.getRect().x - astro.getRect().w, astro.getRect().y - astro.getRect().h, 200, 200 };
			while (curframe_ex < 70) {
				SDL_Rect source_rect = { curframe_ex * 100, 0, 100, 100 };
				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, bgr, NULL, NULL);
				SDL_RenderCopy(renderer, scorebar, NULL, &scorebar_rect);
				SDL_RenderCopy(renderer, explo, &source_rect, &explo_rect);
				Score.setText("Score: " + to_string(score));
				Score.createaText(font_text, renderer);
				SDL_RenderPresent(renderer);
				curframe_ex++;
			}
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, gameover, NULL, NULL);
			SDL_RenderPresent(renderer);

			SDL_Delay(5000);
		}

		// render score text
		Score.setText("Score: " + to_string(score));
		Score.createaText(font_text, renderer);

		// render explosion
		if (curframe_ex < 70) {
			SDL_Rect source_rect = { curframe_ex * 100, 0, 100, 100 };
			SDL_RenderCopy(renderer, explo, &source_rect, &explo_rect);
			curframe_ex++;
		}

		// render shield pick up
		if (!isShield && shield_wait.Paused) {
			SDL_Rect source_shield = { curframe_shield * 32, 0, 32, 32 };
			SDL_RenderCopy(renderer, shield_pickup, &source_shield, &shieldpickup_rect);
			curframe_shield++;
			curframe_shield %= 15;
		}

		// render life_bar
		if (curframe_blood < 11) {
			SDL_Rect source_blood = { curframe_blood * 192, 0, 192, 64 };
			SDL_RenderCopy(renderer, life_bar, &source_blood, &lifebar_rect);
			curframe_blood = (50 - astro.blood) / 5;
		}

		// render energy_bar
		if (curframe_energy >= 0) {
			SDL_Rect source_energy = { curframe_energy * 64, 0, 64, 96 };
			SDL_RenderCopy(renderer, energy, &source_energy, &energy_rect);
			curframe_energy = 10 - (astro.getSkillTime() / (Uint32)1500);
		}

		// render asteroid
		if (curframe_asteroid >= 0) {
			SDL_Rect source_asteroid = { curframe_asteroid * 96, 0, 96, 96 };
			SDL_RenderCopy(renderer, d_astoroid, &source_asteroid, &d_asteroid_rect);
			curframe_asteroid--;
		}

		// render heal
		if (heal_wait.Paused && !isHeal) {
			SDL_Rect source_heal = { curframe_heal * 204, 0, 204, 204 };
			SDL_RenderCopy(renderer, heal_pickup, &source_heal, &heal_rect);
			curframe_heal++;
			curframe_heal %= 10;
		}

		SDL_SetTextureAlphaMod(bgr, 255);
		SDL_RenderPresent(renderer);
	}

	//quit sdl
	RD::quitSDL(window, renderer);
	return 0;
}