#include "rendergame.h"
#include "player.h"
#include "bullet.h"
#include "object.h"
#include "creep.h"
#include "text.h"
#include <vector>
#include <string>
#include <random>

//using namespace rendergame
using namespace RD;

int main(int argc, char* argv[]){
	srand(time(NULL));

	//default feature
    SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	bool quit = false;

	//init SDL
	initSDL(window, renderer);

	// initializ text for score
	Text t;
	t.initText(font_text);
	t.setText("Score: ");

	//load background
	SDL_Texture* bgr = loadTexture(renderer, "E:/personal/Code/C++/LTNC/GameSDL2/WarCraft/WarCraft/bgr.png");

	//initialize player and enemy
	player astro(renderer);
	vector<creep> list_creep;
	
	//default feature
	bool end=false;
	int cnt=0;
	int score=0;
	int level=1;

	//main loop
	while (!quit){
        while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			astro.move(event);
		}
		//render background
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bgr, NULL, NULL);

		//render creep and check shooting
		for (int i = 0; i < 15; i++) {

			creep sEnemy(renderer, SCREEN_WIDTH + i * 200);
			list_creep.push_back(sEnemy);
		}
		for(int i = 0; i < 15; i++) {

			if (!list_creep.at(i).is_killed()) {
				//check astro bullet - enemy
				if (list_creep.at(i).getRect().x<SCREEN_WIDTH){
					if (checkCollision(astro.getRectBullet(),list_creep.at(i).getRect()) && astro.getBullet().is_Move()) {
						list_creep.at(i).kill();
						astro.getBullet().setStatus(false);
						cnt++;
						score=cnt*100;
						if (cnt==15) end=true;
					}
				}

				//check astro - enemy bullet
				if (checkCollision(astro.getRect(),list_creep.at(i).getRectShotback()) ){
					astro.kill();
				}

				//check astro - enemy 
				if (checkCollision(astro.getRect(), list_creep.at(i).getRect())) {
					astro.kill();
					list_creep.at(i).kill();
				}
				
				// enemy move and update enemy
				int opt=rand();	
				list_creep.at(i).move(opt);
				if (list_creep.at(i).getRect().y<=astro.getRect().y+astro.getRect().h/2 && list_creep.at(i).getRect().y>=astro.getRect().y-astro.getRect().h/2) list_creep.at(i).autoshot();
				
				list_creep.at(i).update(renderer);
			}
		}

		//render and update astro by time
		astro.update(renderer);
		if (astro.isKilled() || end){
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