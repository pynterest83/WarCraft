#pragma once

#include "global.h"
#include "gamelogic.h"
#include "menu.h"
#include "rendergame.h"
#include "player.h"
#include "bullet.h"
#include "object.h"
#include "enemy.h"
#include "ebullet.h"

class game {
public:
	game() {};
	~game() {};
	void loadMenu();
	void loadText() {
		Score.initText(font_text, "font/Koulen-Regular.ttf");
		Round.initText(font_text, "font/Koulen-Regular.ttf");
		GameOver1.initText(font_text, "font/Koulen-Regular.ttf");
		GameOver2.initText(font_text, "font/Koulen-Regular.ttf");
		Money.initText(font_text, "font/Koulen-Regular.ttf");
		DisPlayFps.initText(font_text, "font/Koulen-Regular.ttf");
	}
	void loadCharacter();
	void loadSound();
	void loadDefault();
	void loadShield();
	void loadAsteroid();
	void loadHeal();
	void Resetgame();

	void loadSingleGame(player& astro1, vector<enemy>& list_creep, enemy& Boss) {
		shield_wait.Start();
		heal_wait.Start();
		asteroid_wait.Start();
		int frame_rate = 60;
		while (!quit && !Pause) {
			//start frame timer
			frame.Reset();
			frame.Start();

			//event loop
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				handlePause1(astro1);
				handlePause2(astro1);
				handleMute();
				astro1.handleBullet(event);
			}

			//render background
			renderbackground();

			// astro move
			astro1.move();
			int dmg = astro1.damage;

			// set up shield
			setupShield(astro1);

			// set up heal
			setupHeal(astro1);

			// setup asteroid
			setupAsteroid(astro1);
			
			// checkShooting
			check_creep(astro1, list_creep, dmg);
			check_boss(astro1, Boss, list_creep, dmg);

			// change round
			if (Boss.is_killed() && check) {
				Mix_PlayChannel(-1, explo_sound, 0);
				Boss.isBoss = false;
				curframe_ex = 0;
				explo_rect = { Boss.getRect().x - Boss.getRect().w, Boss.getRect().y - Boss.getRect().h, 300, 300 };
				while (curframe_ex < 70) {
					SDL_Rect source_rect = { curframe_ex * 100, 0, 100, 100 };
					SDL_RenderClear(renderer);
					renderbackground();
					SDL_RenderCopy(renderer, explo, &source_rect, &explo_rect);
					SDL_RenderPresent(renderer);
					curframe_ex++;
				}

				type = rand() % 3 + 1 ;
				// regenBoss and Enemy
				level++;
				enemy Boss1(SCREEN_WIDTH - 100, level);
				Boss1.setBoss(level);
				check = false;
				score += 50 * level;
				coin_cnt += 10;
				cnt = 0;
				Boss = Boss1;

				for (int i = 0; i < astro1.num_bullet; i++) {
					astro1.getBullet(i).setStatus(false);
					if (astro1.getBullet(i).is_Move()) astro1.getBullet(i).setPos(0, 0);
				}
				for (int i = 0; i < 5; i++) {
					list_creep.at(i).kill(level + 1);
					enemy sEnemy(SCREEN_WIDTH + i * 200, level);
					list_creep.at(i) = sEnemy;
				}
				// update level
				astro1.speed ++;
				SDL_SetTextureColorMod(bgr[type-1], 150, 150, 150);
				renderbackground();
				Round.setText("ROUND " + to_string(level));
				Round.createaText(font_text, renderer);
				SDL_RenderPresent(renderer);
				SDL_Delay(3000);
			}

			//render and update astro by time
			updatePlayer(astro1, list_creep);

			// render score text
			Score.setText("Score: " + to_string(score));
			Score.createaText(font_text, renderer);

			// render money text
			Money.setText(to_string(coin_cnt));
			Money.createaText(font_text, renderer);

			// render default
			g_Animation(astro1, lifebar_rect, energy_rect);

			// render shield pick up
			if (!isShield && shield_wait.Paused) {
				SDL_Rect source_shield = { curframe_shield * 32, 0, 32, 32 };
				SDL_RenderCopy(renderer, shield_pickup, &source_shield, &shieldpickup_rect);
				curframe_shield++;
				curframe_shield %= 15;
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

			if (astro1.isKilled()) {
				gameOver();
				GameOver1.setText("YOUR SCORE: " + to_string(score));
				GameOver1.createaText(font_text, renderer);
				while (isChoose) {
					renderMenuGameOver();
					if (SDL_PollEvent(&event) != 0) {
						if (event.type == SDL_QUIT) {
							quit = true;
						}
						if (quit) break;
						if (!isChoose) break;
					}
				}
				if (quit) break;
				if (!isChoose) break;
			}
			handleMute();
			SDL_SetTextureColorMod(bgr[type-1], 255, 255, 255);

			// render FPS text
			DisPlayFps.setText(to_string(frame_rate));
			DisPlayFps.createaText(font_text, renderer);

			SDL_RenderPresent(renderer);

			//// check frame
			if (frame.GetTime() < 1000 / FPS) {
				SDL_Delay(1000 / FPS - frame.GetTime());
			}
			frame_rate = 1000 / frame.GetTime();
		}
	}
	void load2Playergame(player& astro1, player& astro2) {
		SDL_Rect p2_life_bar_rect = { SCREEN_WIDTH - 250, 0, 140, 60 };
		SDL_Rect p2_energy_rect = { SCREEN_WIDTH - 300, 0, 40, 60 };
		while (!quit && !Pause) {
			//event loop
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				handlePause11(astro1, astro2);
				handlePause22(astro1, astro2);
				handleMute();
				astro1.handleBullet(event);
				astro2.P2HandleBullet(event);
			}
			//render background
			renderbackground();

			// astro move
			astro1.move();
			astro2.move();
			int dmg1 = astro1.damage;
			int dmg2 = astro2.damage;
			// checkShooting
			check2P(astro1, astro2, dmg1, dmg2);

			updatePlayer2(astro1);
			updatePlayer2(astro2);

			g_Animation(astro2, lifebar_rect, energy_rect);
			g_Animation(astro1, p2_life_bar_rect, p2_energy_rect);
			
			if (astro1.isKilled() || astro2.isKilled()) {
				gameOver();
				if (astro1.isKilled()) {
					GameOver2.setText("PLAYER 2 WIN !!!");
					GameOver2.createaText(font_text, renderer);
				}
				else {
					GameOver2.setText("PLAYER 1 WIN !!!");
					GameOver2.createaText(font_text, renderer);
				}
				while (isChoose) {
					renderMenuGameOver();
					if (SDL_PollEvent(&event) != 0) {
						if (event.type == SDL_QUIT) {
							quit = true;
						}
						if (quit) break;
						if (!isChoose) break;
					}
				}
				if (quit) break;
				if (!isChoose) break;
			}

			handleMute();
			SDL_RenderPresent(renderer);
		}
	}
};
