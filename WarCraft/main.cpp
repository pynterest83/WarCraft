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
	srand(time(NULL));

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
	SDL_Texture* shield = IMG_LoadTexture (renderer, "resources/Shield.png");
	SDL_Texture* life_bar = IMG_LoadTexture(renderer, "resources/lifebar.png");
	
	SDL_Rect scorebar_rect = { 0, 0, SCREEN_WIDTH, 60 };
	SDL_Rect lifebar_rect = { 150, 5, 100, 50 };
	SDL_Rect explo_rect;
	SDL_Rect shield_rect;
	SDL_Rect shieldpickup_rect;
	
	//default feature
	int score = 0;
	int level = 1;
	bool check = true;
	int cnt = 0;
	ifstream f;
	int curframe_ex = 0;
	int curframe_shield = 0;
	int curframe_blood = -1;

	// set Shield
	bool isShield = false;
	Timer shield_wait;
	shield_wait.Start();
	Timer shield_time;
	Timer Shield;
	int x_pos, y_pos;
	
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
	Boss.autoshot();

	//main loop
	while (!quit && !astro.isKilled()) {
		//event loop
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		//render background
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bgr, NULL, NULL);
		SDL_RenderCopy(renderer, scorebar, NULL, &scorebar_rect);

		// astro move
		astro.move();
		
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

		//check shooting
		for (int i = 0; i < 5; i++) {
			if (!list_creep.at(i).is_killed()) {
				//check astro bullet - enemy
				if (list_creep.at(i).getRect().x < SCREEN_WIDTH) {
					if (checkCollision(astro.getRectBullet(), list_creep.at(i).getRect()) && astro.getBullet().is_Move()) {
						curframe_ex = 0;
						 explo_rect = { list_creep.at(i).getRect().x - 50, list_creep.at(i).getRect().y - 50, 200, 200 };

						list_creep.at(i).kill();    
						enemy sEnemy(renderer, SCREEN_WIDTH + i * 200, level);
						list_creep.at(i) = sEnemy;
						astro.getBullet().setStatus(false);
						score += 10 + (level-1)*2;
						cnt++;
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
					list_creep.at(i).kill();
					enemy sEnemy(renderer, SCREEN_WIDTH + i * 200, level);
					list_creep.at(i) = sEnemy;
					score += 10 + (level - 1) * 2;
					cnt++;
				}

				// enemy move and update enemy
				int opt = rand() % 10000;
				list_creep.at(i).move(opt);
				double direct = (double)(astro.getRect().y - list_creep.at(i).getRect().y) / (astro.getRect().x - list_creep.at(i).getRect().x);
				list_creep.at(i).update(renderer, direct);
				if (-sqrt(3)<=direct && direct<=sqrt(3)) list_creep.at(i).autoshot();
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

			SDL_Delay(1000);
		}


		// generate boss
		if (cnt == 15) {
			check = true;
			Boss.isBoss = true;
		}
		if (score >= 150 && check) {
			double direct = (double)(astro.getRect().y - Boss.getRect().y) / (astro.getRect().x - Boss.getRect().x);
			Boss.update(renderer, direct);
			if (-1 <= direct && direct <= 1) Boss.autoshot();
			int opt = rand() % 10000;
			Boss.move(opt);

			if (checkCollision(astro.getRectBullet(), Boss.getRect()) && astro.getBullet().is_Move()) {
				curframe_ex = 0;
				explo_rect = { astro.getRectBullet().x - 10, astro.getRectBullet().y - 10, 100, 100 };

				Boss.kill();
				astro.getBullet().setStatus(false);
			}

			if (checkCollision(astro.getRect(), Boss.getRectShotback())) {
				if (!isShield) {
					curframe_ex = 0;
					explo_rect = { astro.getRect().x - 25, astro.getRect().y - 25, 100, 100 };

					for (int i = 0; i < level; i++) {
						astro.kill();
					}
				}
				Boss.getShotback().setStatus(false);
			}

			if (checkCrash(astro.getRect(), Boss.getRect())) {
				curframe_ex = 0;
				explo_rect = { Boss.getRect().x, Boss.getRect().y, 100, 100 };
				if (!isShield) {
					for (int i = 0; i < level; i++) {
						astro.kill();
					}
				}
				Boss.kill();
			}

			if (Boss.is_killed() && check) {
				curframe_ex = 0;
				explo_rect = { Boss.getRect().x - Boss.getRect().w, Boss.getRect().y-Boss.getRect().h, 300, 300};
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
				Boss.isBoss = false;
				score += 50*level;
				cnt = 0;
				Boss = Boss1;

				for (int i = 0; i < 5; i++) {
					list_creep.at(i).kill();
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
			SDL_Rect source_blood = { 0, curframe_blood * 64, 96, 64 };
			SDL_RenderCopy(renderer, life_bar, &source_blood, &lifebar_rect);
			curframe_blood = (50 - astro.blood) / 5;
		}
		SDL_SetTextureAlphaMod(bgr, 255);
		SDL_RenderPresent(renderer);
	}

	//quit sdl
	RD::quitSDL(window, renderer);
	return 0;
}