#include "gamelogic.h"

// 2 status: shield on, shield off
void setupShield(player& astro1) {
	// shield off
	if (!isShield) {
		// wait 10s to spawn shield
		if (shield_wait.GetTime() > (Uint32)10000) {
			// if shield is spawned and shield_time not start yet: start shield time
			if (!shield_wait.Paused && !shield_time.Started) shield_time.Start();
			// pause shield wait
			shield_wait.Pause();
			// spawn shield
			shieldpickup_rect = { x_pos, y_pos, 50, 50 };
			// if shield is picked up
			if (checkCollision(shieldpickup_rect, astro1.getRect())) {
				Mix_PlayChannel(-1, picked, 0);
				// reset shield wait
				shield_wait.Reset();
				// set shield on
				isShield = true;
				Shield.Start();
			}
			// if shield time > 10s and not picked up: reset shield time and shield wait
			if (shield_time.GetTime() > (Uint32)10000) {
				shield_wait.Reset();
				shield_wait.Unpause();
				shield_wait.Start();
				shield_time.Reset();
			}
		}
		// if shield wait < 10s: random position to spawn shield
		else {
			x_pos = rand() % 600;
			y_pos = rand() % 600;
			if (y_pos <= 60) y_pos += 100;
		}
	}

	// shield on
	if (isShield)
	{
		// render shield
		shield_rect = { astro1.getRect().x - 30, astro1.getRect().y - 20, 100, 100 };
		SDL_RenderCopy(renderer, shield, NULL, &shield_rect);
		// if shield time > 12s: set shield off and restart shield wait
		if (Shield.GetTime() > (Uint32)(12000)) {
			isShield = false;
			shield_wait.Unpause();
			shield_wait.Start();
		}
	}
}

// heal the same as shield
void setupHeal(player& astro1) {
	if (!isHeal) {
		if (heal_wait.GetTime() > (Uint32)10000 && astro1.blood < 20) {
			if (!heal_wait.Paused && !heal_time.Started) heal_time.Start();
			heal_wait.Pause();
			heal_rect = { x_heal, y_heal, 50, 50 };
			if (checkCollision(heal_rect, astro1.getRect())) {
				Mix_PlayChannel(-1, picked, 0);
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
		astro1.blood += 10;
		isHeal = false;
		heal_wait.Unpause();
		heal_wait.Start();
	}
}

// 2 status: asteroid is flying and not
void setupAsteroid(player& astro1) {
	// flying and not destroyed
	if (!isDes) {
		// if waited end
		if (asteroid_wait.GetTime() > (Uint32)wait_time) {
			// flying, play sound and render
			Mix_PlayChannel(-1, asteroid, 0);
			asteroid_wait.Pause();
			f_asteroid_rect.x -= 15;
			f_asteroid_rect.y -= directA * 15;
			angle -= 30;
			SDL_RenderCopyEx(renderer, f_asteroid, NULL, &f_asteroid_rect, angle, NULL, SDL_FLIP_NONE);
			
			// cases to destroy asteroid
			if (checkCollision(f_asteroid_rect, astro1.getRect())) {
				isDes = true;
				if (!isShield) {
					curframe_ex = 0;
					explo_rect = { astro1.getRect().x + 10, astro1.getRect().y + 10, 75, 75 };

					astro1.kill(1);
				}
				else Mix_PlayChannel(-1, shield_hit, 0);
			}
			if (f_asteroid_rect.x <= 0 || f_asteroid_rect.y >= SCREEN_HEIGHT || f_asteroid_rect.y <= 0) {
				isDes = true;
			}
		}
		// if waited not end: random position to spawn asteroid and detect direction
		else {
			y_start = rand() % 600 + 60;
			f_asteroid_rect = { x_start, y_start, 96, 96 };
			directA = (double)(astro1.getRect().y - f_asteroid_rect.y) / (astro1.getRect().x - f_asteroid_rect.x);
		}
	}

	// not flying and destroyed
	else {
		// render destroying animation
		d_asteroid_rect = { f_asteroid_rect.x - 20, f_asteroid_rect.y - 20 , 150, 150 };
		curframe_asteroid = 7;

		// if animation end: reset asteroid
		isDes = false;
		asteroid_wait.Reset();
		asteroid_wait.Start();
		wait_time = rand() % 10000 + 5000;
	}
}

// render background
void renderbackground() {
	SDL_RenderClear(renderer);

	// render background
	SDL_RenderCopy(renderer, bgr[type-1], NULL, &bgr_rect);
	SDL_Rect next_bgr = { bgr_rect.x + SCREEN_WIDTH, bgr_rect.y, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy(renderer, bgr[type-1], NULL, &next_bgr);

	// render score bar and pause rect, coin rect
	SDL_RenderCopy(renderer, scorebar, NULL, &scorebar_rect);
	SDL_RenderCopy(renderer, coin, NULL, &coin_rect1);
	SDL_RenderCopy(renderer, pause, NULL, &pause_rect);

	// rolling background
	bgr_rect.x--;
	if (bgr_rect.x <= -SCREEN_WIDTH) bgr_rect.x = 0;
}

// check interaction
void check_creep(player& astro1, vector<enemy>& list_creep, int& dmg) {
	for (int i = 0; i < 5; i++) {
		if (!list_creep.at(i).is_killed()) {
			//check astro bullet - enemy
			if (list_creep.at(i).getRect().x + list_creep.at(i).getRect().w < SCREEN_WIDTH) {
				for (int j = 0; j < astro1.num_bullet; j++) {
					if (checkCollision(astro1.getRectBullet(j), list_creep.at(i).getRect()) && astro1.getBullet(j).is_Move()) {
						list_creep.at(i).kill(dmg);

						// if bullet hit
						if (list_creep.at(i).is_killed()) {
							Mix_PlayChannel(-1, explo_sound, 0);
							// set explosion position
							curframe_ex = 0;
							explo_rect = { list_creep.at(i).getRect().x - 50, list_creep.at(i).getRect().y - 50, 200, 200 };
							enemy sEnemy(SCREEN_WIDTH + i * 200, level);
							sEnemy.setImg(creep[type - 1][i % 5]);
							list_creep.at(i) = sEnemy;
							score += 10 + (level - 1) * 2;
							coin_cnt++;
							cnt++;
						}

						else {
							curframe_ex = 0;
							explo_rect = { list_creep.at(i).getRect().x, list_creep.at(i).getRect().y, 50, 50 };
						}
						astro1.getBullet(j).setStatus(false);
					}
				}
				
				// check supporter bullet - enemy
				for (int k = 0; k < 20; k++) {
					if (checkCollision(astro1.getSup().getspShot(k).getRect(), list_creep.at(i).getRect()) && astro1.SupIsSet) {
						list_creep.at(i).kill(dmg);
						if (list_creep.at(i).is_killed()) {
							Mix_PlayChannel(-1, explo_sound, 0);
							curframe_ex = 0;
							explo_rect = { list_creep.at(i).getRect().x - 50, list_creep.at(i).getRect().y - 50, 200, 200 };
							enemy sEnemy(SCREEN_WIDTH + i * 200, level);
							list_creep.at(i) = sEnemy;
							score += 10 + (level - 1) * 2;
							coin_cnt++;
							cnt++;
						}

						else {
							curframe_ex = 0;
							explo_rect = { list_creep.at(i).getRect().x, list_creep.at(i).getRect().y, 50, 50 };
						}
						astro1.getSup().getspShot(k).setStatus(false);
					}
				}
			}

			//check astro - enemy bullet
			if (checkCollision(astro1.getRect(), list_creep.at(i).getRectShotback())) {
				if (!isShield) {
					curframe_ex = 0;
					explo_rect = { astro1.getRect().x + 10, astro1.getRect().y + 10, 50, 50 };

					astro1.kill(1);
				}
				else Mix_PlayChannel(-1, shield_hit, 0);
				list_creep.at(i).getShotback().setStatus(false);
			}

			//check astro - enemy 
			if (checkCrash(astro1.getRect(), list_creep.at(i).getRect())) {
				curframe_ex = 0;
				explo_rect = { list_creep.at(i).getRect().x - 50, list_creep.at(i).getRect().y - 50, 200, 200 };

				if (!isShield) astro1.kill(1);
				else Mix_PlayChannel(-1, shield_hit, 0);
				list_creep.at(i).kill(level + 1);
				Mix_PlayChannel(-1, explo_sound, 0);
				enemy sEnemy(SCREEN_WIDTH + i * 200, level);
				list_creep.at(i) = sEnemy;
				score += 10 + (level - 1) * 2;
				coin_cnt++;
				cnt++;
			}

			// enemy move and update enemy depend on direct
			int opt = rand() % 10000;
			double direct = (double)(astro1.getRect().y - list_creep.at(i).getRect().y) / (astro1.getRect().x - list_creep.at(i).getRect().x);
			list_creep.at(i).move(opt, astro1.getRect().y, direct);
			list_creep.at(i).update(renderer, direct);
			if (type == 2) {
				if (-sqrt(3) <= direct && direct <= sqrt(3)) list_creep.at(i).autoshot();
			}
			else if (type == 1){
				if (checkSeen(astro1.getRect(), list_creep.at(i).getRect())) list_creep.at(i).autoshot();
			}
			else {
				list_creep.at(i).autoshot();
			}
		}
	}
}

// check interaction with boss
void check_boss(player& astro1, enemy& Boss, vector<enemy>& list_creep, int& dmg) {
	// start to render boss
	if (cnt == 15) {
		check = true;
		Boss.isBoss = true;
	}
	// check interation
	if (score >= 150 && check) {
		// check all of bullet out of screen
		bool out_of_screen = true;

		double direct = (double)((double)astro1.getRect().y - Boss.getRect().y) / ((double)astro1.getRect().x - Boss.getRect().x);
		Boss.update(renderer, direct);
		if (type == 1) {
			for (int i = 0; i < 20; i++) {
				if (Boss.getbossShot(i).is_Move()) {
					out_of_screen = false;
					break;
				}
			}
			// all bullet out of screen start another shoot
			if (out_of_screen) Boss.bossautoshot();
		}
		else Boss.bossautoshot();

		// move enemy up and down
		int opt = rand() % 10000;
		Boss.move(opt, astro1.getRect().y, direct);

		// check player bullet - boss
		for (int j = 0; j < astro1.num_bullet; j++) {
			if (checkCollision(astro1.getRectBullet(j), Boss.getRect()) && astro1.getBullet(j).is_Move() && Boss.getRect().x + Boss.getRect().w < SCREEN_WIDTH) {
				curframe_ex = 0;
				explo_rect = { astro1.getRectBullet(j).x - 10, astro1.getRectBullet(j).y - 10, 100, 100 };

				Boss.kill(dmg);
				astro1.getBullet(j).setStatus(false);
			}
		}
		// check supporter bullet - boss
		for (int i = 0; i < 20; i++) {
			if (checkCollision(astro1.getSup().getspShot(i).getRect(), Boss.getRect()) && astro1.SupIsSet) {
				curframe_ex = 0;
				explo_rect = { astro1.getSup().getRectShotback().x - 10, astro1.getSup().getRectShotback().y - 10, 100, 100 };

				Boss.kill(dmg);
				astro1.getSup().getspShot(i).setStatus(false);
			}
		}
		// check boss bullet - player
		for (int i = 0; i < 20; i++) {
			if (checkCollision(astro1.getRect(), Boss.getbossShot(i).getRect())) {
				if (!isShield) {
					curframe_ex = 0;
					explo_rect = { astro1.getRect().x - 25, astro1.getRect().y - 25, 100, 100 };

					for (int i = 0; i < level; i++) {
						astro1.kill(1);
					}
				}
				else Mix_PlayChannel(-1, shield_hit, 0);
				Boss.getbossShot(i).setStatus(false);
			}
		}
		// check crash
		if (checkCrash(astro1.getRect(), Boss.getRect())) {
			curframe_ex = 0;
			explo_rect = { Boss.getRect().x, Boss.getRect().y, 100, 100 };
			if (!isShield) {
				for (int i = 0; i < level; i++) {
					astro1.kill(1);
				}
			}
			else Mix_PlayChannel(-1, shield_hit, 0);
			Boss.kill(level + 1);
		}
	}
}

// update player for the first gametype
void updatePlayer(player& astro1, vector<enemy>& list_creep){

	// update player and take the direct parameter for player's support
	if (!astro1.isP2) {
		double direct = (double)(astro1.getSup().getRect().y - list_creep.at(0).getRect().y) / (astro1.getSup().getRect().x - list_creep.at(0).getRect().x);
		astro1.update(renderer, direct);
	}
	else astro1.P2update(renderer);

	// if player is dead, render big explosion 
	if (astro1.isKilled()) {
		curframe_ex = 0;
		explo_rect = { astro1.getRect().x - astro1.getRect().w, astro1.getRect().y - astro1.getRect().h, 200, 200 };
		while (curframe_ex < 70) {
			SDL_Rect source_rect = { curframe_ex * 100, 0, 100, 100 };
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, bgr[type-1], NULL, NULL);
			SDL_RenderCopy(renderer, explo, &source_rect, &explo_rect);
			SDL_RenderPresent(renderer);
			curframe_ex++;
		}
	}
}

// update player for the second gametype
void updatePlayer2(player& astro) {
	// update player
	if (!astro.isP2) {
		astro.update(renderer, 0);
	}
	else astro.P2update(renderer);

	// check if one of 2 player is killed
	if (astro.isKilled()) {
		curframe_ex = 0;
		explo_rect = { astro.getRect().x - astro.getRect().w, astro.getRect().y - astro.getRect().h, 200, 200 };
		while (curframe_ex < 70) {
			SDL_Rect source_rect = { curframe_ex * 100, 0, 100, 100 };
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, bgr[type - 1], NULL, NULL);
			SDL_RenderCopy(renderer, explo, &source_rect, &explo_rect);
			SDL_RenderPresent(renderer);
			curframe_ex++;
		}
	}
}

// rendergame over
void gameOver() {
	Mix_PlayChannel(-1, explo_sound, 0);

	// open highscore and money to update
	highscore.open("highscore.txt", ios::app);
	highscore << score << " ";
	money.open("coin.txt", ios::in);
	money >> coin_sum;
	money.close();
	money.open("coin.txt", ios::out);
	coin_sum += coin_cnt;
	money << coin_sum;

	// render bge gameover
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, gameover, NULL, NULL);

	highscore.close();
	money.close();
}

// some default animation
void g_Animation(player& astro1, SDL_Rect &lifebar_rect, SDL_Rect& energy_rect) {
	// render explosion
	if (curframe_ex < 70) {
		SDL_Rect source_rect = { curframe_ex * 100, 0, 100, 100 };
		SDL_RenderCopy(renderer, explo, &source_rect, &explo_rect);
		curframe_ex++;
	}

	// render life_bar
	if (curframe_blood < 11) {
		SDL_Rect source_blood = { curframe_blood * 192, 0, 192, 64 };
		SDL_RenderCopy(renderer, life_bar, &source_blood, &lifebar_rect);
		curframe_blood = (50 - astro1.blood) / 5;
	}

	// render energy_bar
	if (curframe_energy >= -1) {
		SDL_Rect source_energy = { curframe_energy * 64, 0, 64, 96 };
		SDL_RenderCopy(renderer, energy, &source_energy, &energy_rect);
		curframe_energy = 10 - (astro1.getSkillTime() / (Uint32)1500);
	}
}

// check interaction between 2 player
void check2P(player& astro1, player& astro2, int& dmg1, int& dmg2) {
	for (int j = 0; j < astro1.num_bullet; j++) {
		if (checkCollision(astro1.getRectBullet(j), astro2.getRect()) && astro1.getBullet(j).is_Move()) {
			curframe_ex = 0;
			explo_rect = { astro1.getRectBullet(j).x - 10, astro1.getRectBullet(j).y - 10, 100, 100 };

			astro2.kill(dmg1);
			astro1.getBullet(j).setStatus(false);
		}
	}

	for (int j = 0; j < astro2.num_bullet; j++) {
		if (checkCollision(astro2.getRectBullet(j), astro1.getRect()) && astro2.getBullet(j).is_Move()) {
			curframe_ex = 0;
			explo_rect = { astro2.getRectBullet(j).x - 30, astro2.getRectBullet(j).y - 30, 100, 100 };

			astro1.kill(dmg2);
			astro2.getBullet(j).setStatus(false);
		}
	}

	if (checkCrash(astro1.getRect(), astro2.getRect())) {
		curframe_ex = 0;
		explo_rect = { astro1.getRect().x, astro1.getRect().y, 100, 100 };

		astro1.kill(5);
		astro2.kill(5);
	}
}

// handle pause by ESC
void handlePause1(player& astro1) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			// pause all timers
			Pause = true;
			shield_wait.Pause();
			heal_wait.Pause();
			asteroid_wait.Pause();
			Shield.Pause();
			shield_time.Pause();
			heal_time.Pause();
			astro1.skill_time.Pause();
			astro1.skill_wait.Pause();
			while (Pause) {
				// while pause renderMenuPause
				handleMute();
				renderMenuPause();
				if (!Pause) {
					// if unpause, unpause all timer
					shield_wait.Unpause();
					heal_wait.Unpause();
					asteroid_wait.Unpause();
					Shield.Unpause();
					shield_time.Unpause();
					heal_time.Unpause();
					astro1.skill_time.Unpause();
					astro1.skill_wait.Unpause();
				}
				if (SDL_PollEvent(&event) != 0) {
					if (event.type == SDL_QUIT) {
						quit = true;
					}
					if (quit) break;
					if (!isChoose) break;
				}
			}
		}
	}
}

// handle pause by pause button
void handlePause2(player& astro1) {
	SDL_GetMouseState(&mouse.x, &mouse.y);
	mouse.x *= scaleX;
	mouse.y *= scaleY;
	if (SDL_PointInRect(&mouse, &pause_rect)) {
		SDL_SetTextureColorMod(pause, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			Pause = true;
			shield_wait.Pause();
			heal_wait.Pause();
			asteroid_wait.Pause();
			Shield.Pause();
			shield_time.Pause();
			heal_time.Pause();
			astro1.skill_time.Pause();
			astro1.skill_wait.Pause();
			while (Pause) {
				handleMute();
				renderMenuPause();
				if (!Pause) {
					shield_wait.Unpause();
					heal_wait.Unpause();
					asteroid_wait.Unpause();
					Shield.Unpause();
					shield_time.Unpause();
					heal_time.Unpause();
					astro1.skill_time.Unpause();
					astro1.skill_wait.Unpause();
				}
				if (SDL_PollEvent(&event) != 0) {
					if (event.type == SDL_QUIT) {
						quit = true;
					}
					if (quit) break;
					if (!isChoose) break;
				}
			}
		}
	}
	else SDL_SetTextureColorMod(pause, 150, 150, 150);
}

// handle pause with gametype 2
void handlePause11(player& astro1, player& astro2) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			Pause = true;
			astro1.skill_time.Pause();
			astro1.skill_wait.Pause();
			astro2.skill_time.Pause();
			astro2.skill_wait.Pause();
			while (Pause) {
				handleMute();
				renderMenuPause();
				if (!Pause) {
					astro1.skill_time.Unpause();
					astro1.skill_wait.Unpause();
					astro2.skill_time.Unpause();
					astro2.skill_wait.Unpause();
				}
				if (SDL_PollEvent(&event) != 0) {
					if (event.type == SDL_QUIT) {
						quit = true;
					}
					if (quit) break;
					if (!isChoose) break;
				}
			}
		}
	}
}

// handle pause with mouse gametype2
void handlePause22(player& astro1, player& astro2) {
	SDL_GetMouseState(&mouse.x, &mouse.y);
	mouse.x *= scaleX;
	mouse.y *= scaleY;
	if (SDL_PointInRect(&mouse, &pause_rect)) {
		SDL_SetTextureColorMod(pause, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			Pause = true;
			astro1.skill_time.Pause();
			astro1.skill_wait.Pause();
			astro2.skill_time.Pause();
			astro2.skill_wait.Pause();
			while (Pause) {
				handleMute();
				renderMenuPause();
				if (!Pause) {
					astro1.skill_time.Pause();
					astro1.skill_wait.Pause();
					astro2.skill_time.Pause();
					astro2.skill_wait.Pause();
				}
				if (SDL_PollEvent(&event) != 0) {
					if (event.type == SDL_QUIT) {
						quit = true;
					}
					if (quit) break;
					if (!isChoose) break;
				}
			}
		}
	}
	else SDL_SetTextureColorMod(pause, 150, 150, 150);
}

// handle mute in game play
void handleMute() {
	SDL_RenderCopy(renderer, SOUND, NULL, &sound_rect);
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (isFullScreen) {
		mouse.x *= scaleX;
		mouse.y *= scaleY;
	}
	if (SDL_PointInRect(&mouse, &sound_rect)) {
		SDL_SetTextureColorMod(SOUND, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			if (!isMute) {
				// set all volume music and chunk to 0
				Mix_VolumeMusic(0);
				for (int i = 0; i < 8; i++) {
					Mix_VolumeChunk(chunk[i], 0);
				}
				SOUND = sound[1];
				isMute = true;
			}
			// else reset the volume level in settings
			else {
				Mix_VolumeMusic((gfx_control.w) * 30 * 1.0 / 600);
				for (int i = 0; i < 8; i++) {
					if (i == 2) Mix_VolumeChunk(chunk[i], (sfx_control.w) * 30 * 1.0 / 600);
					else if (i == 0 || i == 1) Mix_VolumeChunk(chunk[i], (sfx_control.w) * 50 * 1.0 / 600);
					else Mix_VolumeChunk(chunk[i], (sfx_control.w) * 128 * 1.0 / 600);
				}
				SOUND = sound[0];
				isMute = false;
			}
		}
	}
	else SDL_SetTextureColorMod(SOUND, 150, 150, 150);
}