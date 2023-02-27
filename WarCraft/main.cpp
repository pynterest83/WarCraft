#include "rendergame.h"
#include "player.h"
#include "bullet.h"
#include "object.h"
#include "creep.h"
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

	// initializ text for score
	Text t;
	t.initText(font_text);
	t.setText("Score: ");

	//load background
	SDL_Texture* bgr = IMG_LoadTexture(renderer, "bgr.png");
	SDL_Texture *scorebar = IMG_LoadTexture(renderer, "scorebar.png");
	SDL_Rect scorebar_rect = { 0, 0, SCREEN_WIDTH, 60 };

	//initialize player and enemy
	player astro(renderer);
	vector<creep> list_creep;
	for (int i = 0; i < 5; i++) {
		creep sEnemy(renderer, SCREEN_WIDTH + i * 200);
		list_creep.push_back(sEnemy);
	}

	creep Boss(renderer, SCREEN_WIDTH - 100);
	Boss.setBoss(renderer);
	Boss.autoshot();

	//default feature
	int score=0;
	int level=1;

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
						creep sEnemy(renderer, SCREEN_WIDTH + i * 200);
						list_creep.at(i) = sEnemy;
						astro.getBullet().setStatus(false);
						score+=10;
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
					creep sEnemy(renderer, SCREEN_WIDTH + i * 200);
					list_creep.at(i) = sEnemy;
					score += 10;
				}

				// enemy move and update enemy
				int opt = rand();
				list_creep.at(i).move(opt);
				list_creep.at(i).update(renderer, astro.getRect(), list_creep.at(i).getRect());
				if (astro.getRect().x + astro.getRect().h < list_creep.at(i).getRect().x - 20) list_creep.at(i).autoshot();
			}
		}
		
		Boss.update(renderer, astro.getRect(), Boss.getRect());
		//render and update astro by time
		astro.update(renderer);
		if (astro.isKilled()){
			quit=true;
		}

		// render score text
		t.setText("Score: " + to_string(score));
		t.createaText(font_text, renderer);

		SDL_RenderPresent(renderer);
    }
	
	//quit sdl
	RD::quitSDL(window, renderer);
	return 0;
}