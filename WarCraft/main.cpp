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

	//load background
	SDL_Texture* bgr = IMG_LoadTexture(renderer, "resources/bgr.png");
	SDL_Texture* scorebar = IMG_LoadTexture(renderer, "resources/scorebar.png");
	SDL_Texture* explo = IMG_LoadTexture(renderer, "resources/explosion2.png");
	SDL_Texture* gameover = IMG_LoadTexture(renderer, "resources/gameover.png");
	SDL_Rect scorebar_rect = { 0, 0, SCREEN_WIDTH, 60 };
	SDL_Rect explo_rect;
	
	//default feature
	int score = 0;
	int level = 1;
	bool check = true;
	int cnt = 0;
	ifstream f;
	const int frame = 70;
	int curframe=0;

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

		astro.move();

		//check shooting
		for (int i = 0; i < 5; i++) {
			if (!list_creep.at(i).is_killed()) {
				//check astro bullet - enemy
				if (list_creep.at(i).getRect().x < SCREEN_WIDTH) {
					if (checkCollision(astro.getRectBullet(), list_creep.at(i).getRect()) && astro.getBullet().is_Move()) {
						curframe = 0;
						explo_rect = { list_creep.at(i).getRect().x - 50, list_creep.at(i).getRect().y - 50, 200, 200 };

						list_creep.at(i).kill();    
						enemy sEnemy(renderer, SCREEN_WIDTH + i * 200, level);
						list_creep.at(i) = sEnemy;
						astro.getBullet().setStatus(false);
						score += 10;
						cnt++;
					}
				}

				//check astro - enemy bullet
				if (checkCollision(astro.getRect(), list_creep.at(i).getRectShotback())) {
					curframe = 0;
					explo_rect = { astro.getRect().x + 10, astro.getRect().y + 10, 50, 50};

					astro.kill();
					list_creep.at(i).getShotback().setStatus(false);
				}

				//check astro - enemy 
				if (checkCrash(astro.getRect(), list_creep.at(i).getRect())) {
					curframe = 0;
					explo_rect = { list_creep.at(i).getRect().x - 50, list_creep.at(i).getRect().y - 50, 200, 200 };

					astro.kill();
					list_creep.at(i).kill();
					enemy sEnemy(renderer, SCREEN_WIDTH + i * 200, level);
					list_creep.at(i) = sEnemy;
					score += 10;
					cnt++;
				}

				// enemy move and update enemy
				int opt = rand() % 10000;
				list_creep.at(i).move(opt);
				list_creep.at(i).update(renderer, astro.getRect(), list_creep.at(i).getRect());
				double direct = (double)(astro.getRect().y - list_creep.at(i).getRect().y) / (astro.getRect().x - list_creep.at(i).getRect().x);
				if (-sqrt(3)<=direct && direct<=sqrt(3)) list_creep.at(i).autoshot();
			}
		}

		//render and update astro by time
		astro.update(renderer);
		if (astro.isKilled() && check) {	
			curframe = 0;
			explo_rect = { astro.getRect().x - astro.getRect().w, astro.getRect().y - astro.getRect().h, 200, 200 };
			while (curframe < 70) {
				SDL_Rect source_rect = { curframe * 100, 0, 100, 100 };
				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, bgr, NULL, NULL);
				SDL_RenderCopy(renderer, scorebar, NULL, &scorebar_rect);
				SDL_RenderCopy(renderer, explo, &source_rect, &explo_rect);
				Score.setText("Score: " + to_string(score));
				Score.createaText(font_text, renderer);
				SDL_RenderPresent(renderer);
				curframe++;
			}
			SDL_RenderCopy(renderer, gameover, NULL, NULL);
			SDL_RenderPresent(renderer);

			SDL_Delay(100);
		}


		// generate boss
		if (cnt == 15) check = true;
		if (score >= 150 && check) {
			Boss.update(renderer, astro.getRect(), Boss.getRect());
			double direct = (double)(astro.getRect().y - Boss.getRect().y) / (astro.getRect().x - Boss.getRect().x);
			if (-1 <= direct && direct <= 1) Boss.autoshot();
			int opt = rand() % 10000;
			Boss.move(opt);

			if (checkCollision(astro.getRectBullet(), Boss.getRect()) && astro.getBullet().is_Move()) {
				curframe = 0;
				explo_rect = { astro.getRectBullet().x + 10, astro.getRectBullet().y + 10, 100, 100 };

				Boss.kill();
				astro.getBullet().setStatus(false);
			}

			if (checkCollision(astro.getRect(), Boss.getRectShotback())) {
				curframe = 0;
				explo_rect = { astro.getRect().x - 25, astro.getRect().y -25, 100, 100 };

				for (int i = 0; i < level; i++) {
					astro.kill();
				}
				Boss.getShotback().setStatus(false);
			}

			if (checkCrash(astro.getRect(), Boss.getRect())) {
				curframe = 0;
				explo_rect = { Boss.getRect().x, Boss.getRect().y, 100, 100 };

				for (int i = 0; i < level; i++) {
					astro.kill();
				}
				Boss.kill();
			}

			if (Boss.is_killed() && check) {
				curframe = 0;
				explo_rect = { Boss.getRect().x - Boss.getRect().w, Boss.getRect().y-Boss.getRect().h, 300, 300};
				while (curframe < 70) {
					SDL_Rect source_rect = { curframe * 100, 0, 100, 100 };
					SDL_RenderClear(renderer);
					SDL_RenderCopy(renderer, bgr, NULL, NULL);
					SDL_RenderCopy(renderer, scorebar, NULL, &scorebar_rect);
					SDL_RenderCopy(renderer, explo, &source_rect, &explo_rect);
					Score.setText("Score: " + to_string(score));
					Score.createaText(font_text, renderer);
					SDL_RenderPresent(renderer);
					curframe++;
				}

				// regenBoss and Enemy
				enemy Boss1(renderer, SCREEN_WIDTH - 100, level);
				Boss1.setBoss(renderer, level);
				check = false;
				score += 50;
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
		if (curframe< 70) {
			SDL_Rect source_rect = { curframe * 100, 0, 100, 100 };
			SDL_RenderCopy(renderer, explo, &source_rect, &explo_rect);
			curframe++;
		}

		SDL_SetTextureAlphaMod(bgr, 255);
		SDL_RenderPresent(renderer);
	}

	//quit sdl
	RD::quitSDL(window, renderer);
	return 0;
}