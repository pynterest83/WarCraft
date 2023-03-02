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

//using namespace rendergame
using namespace RD;
using namespace std;

int main(int argc, char* argv[]){
	srand(time(NULL));

	//default feature
    SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;
	bool quit = false;

	//init SDL
	initSDL(window, renderer);

	// initialize text
	Text Score(5,5,50,100,1);
	Score.initText(font_text, "font/Koulen-Regular.ttf");
	Text Round(SCREEN_WIDTH/2-175, SCREEN_HEIGHT/2-40, 80, 350, 1);
	Round.initText(font_text, "font/Koulen-Regular.ttf");

	//load background
	SDL_Texture* bgr = IMG_LoadTexture(renderer, "resources/bgr.png");
	SDL_Texture *scorebar = IMG_LoadTexture(renderer, "resources/scorebar.png");
	SDL_Rect scorebar_rect = { 0, 0, SCREEN_WIDTH, 60 };

	//default feature
	int score = 0;
	int level = 1;
	bool check = true;
	int cnt = 0;

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
	while (!quit){
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
		for(int i = 0; i < 5; i++) {
			if (!list_creep.at(i).is_killed()) {
				//check astro bullet - enemy
				if (list_creep.at(i).getRect().x<SCREEN_WIDTH){
					if (checkCollision(astro.getRectBullet(),list_creep.at(i).getRect()) && astro.getBullet().is_Move()) {
						list_creep.at(i).kill();
						enemy sEnemy(renderer, SCREEN_WIDTH + i * 200, level);
						list_creep.at(i) = sEnemy;
						astro.getBullet().setStatus(false);
						score+=10;
						cnt++;
					}
				}

				//check astro - enemy bullet
				if (checkCollision(astro.getRect(),list_creep.at(i).getRectShotback()) ){
					astro.kill();
					list_creep.at(i).getShotback().setStatus(false);
				}

				//check astro - enemy 
				if (checkCrash(astro.getRect(), list_creep.at(i).getRect())) {
					SDL_Delay(500);
					astro.kill();
					list_creep.at(i).kill();
					enemy sEnemy(renderer, SCREEN_WIDTH + i * 200, level);
					list_creep.at(i) = sEnemy;
					score += 10;
					cnt++;
				}

				// enemy move and update enemy
				int opt = rand()%10000;
				list_creep.at(i).move(opt);
				list_creep.at(i).update(renderer, astro.getRect(), list_creep.at(i).getRect());
				if (astro.getRect().x + astro.getRect().w < list_creep.at(i).getRect().x) list_creep.at(i).autoshot();
			}
		}

		//render and update astro by time
		astro.update(renderer);
		if (astro.isKilled()){
			quit=true;
		}


		// generate boss
		if (cnt == 15) check = true;
		if (score >= 150 && check) {
			Boss.update(renderer, astro.getRect(), Boss.getRect());
			if (astro.getRect().x + astro.getRect().w < Boss.getRect().x) Boss.autoshot();
			int opt = rand() % 10000;
			Boss.move(opt);

			if (checkCollision(astro.getRectBullet(), Boss.getRect()) && astro.getBullet().is_Move()) {
				Boss.kill();
				astro.getBullet().setStatus(false);
			}

			if (checkCollision(astro.getRect(), Boss.getRectShotback())) {
				for (int i = 0; i < level; i++) {
					astro.kill();
				}
				Boss.getShotback().setStatus(false);
			}

			if (checkCrash(astro.getRect(), Boss.getRect())) {
				SDL_Delay(500);
				for (int i = 0; i < level; i++) {
					astro.kill();
				}
				Boss.kill();
			}

			if (Boss.is_killed() && check) {
				enemy Boss1(renderer, SCREEN_WIDTH - 100, level);
				Boss1.setBoss(renderer, level);
				check = false;
				score += 50;
				cnt = 0;
				Boss = Boss1;

				// update level
				level++;
				SDL_SetTextureAlphaMod(bgr, 150);
				SDL_RenderCopy(renderer, bgr, NULL, NULL);
				Round.setText("ROUND " + to_string(level));
				Round.createaText(font_text, renderer);
				Score.setText("Score: " + to_string(score));
				Score.createaText(font_text, renderer);
				SDL_RenderPresent(renderer);

				// reset
				SDL_Delay(3000);
				for (int i = 0; i < 5; i++) {
					list_creep.at(i).kill();
					enemy sEnemy(renderer, SCREEN_WIDTH + i * 200, level);
					list_creep.at(i) = sEnemy;
				}
			}
		}

		// render score text
		Score.setText("Score: " + to_string(score));
		Score.createaText(font_text, renderer);

		SDL_SetTextureAlphaMod(bgr, 255);
		SDL_RenderPresent(renderer);
    }
	
	//quit sdl
	RD::quitSDL(window, renderer);
	return 0;
}