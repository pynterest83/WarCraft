#include "game.h"
void game::loadMenu() {
	menu = IMG_LoadTexture(renderer, "resources/menubgr.png");
	start = IMG_LoadTexture(renderer, "resources/start.png");
	game_exit = IMG_LoadTexture(renderer, "resources/exit.png");
	mode1P = IMG_LoadTexture(renderer, "resources/pve.png");
	mode2P = IMG_LoadTexture(renderer, "resources/pvp.png");
	back = IMG_LoadTexture(renderer, "resources/back.png");
	pause = IMG_LoadTexture(renderer, "resources/pause.png");
	pauseheader = IMG_LoadTexture(renderer, "resources/pauseheader.png");
	pausewindow = IMG_LoadTexture(renderer, "resources/pausewindow.png");
	replay = IMG_LoadTexture(renderer, "resources/replay.png");
	game_quit = IMG_LoadTexture(renderer, "resources/gamequit.png");
	game_continue = IMG_LoadTexture(renderer, "resources/continue.png");
	record = IMG_LoadTexture(renderer, "resources/highscore.png");
	rec_but = IMG_LoadTexture(renderer, "resources/window.png");
	rec_header = IMG_LoadTexture(renderer, "resources/recordheader.png");
	inf_but = IMG_LoadTexture(renderer, "resources/window.png");
	info_header = IMG_LoadTexture(renderer, "resources/infoheader.png");
	info = IMG_LoadTexture(renderer, "resources/information.jpg");
	sound[0] = IMG_LoadTexture(renderer, "resources/sound1.png");
	sound[1] = IMG_LoadTexture(renderer, "resources/sound2.png");
	SOUND = sound[0];
	settings = IMG_LoadTexture(renderer, "resources/settings.png");
	zoom = IMG_LoadTexture(renderer, "resources/Zoom.png");
	set_but = IMG_LoadTexture(renderer, "resources/set_but.png");
	slider1 = IMG_LoadTexture(renderer, "resources/slider.png");
	slider2 = IMG_LoadTexture(renderer, "resources/slider.png");
	gfx = IMG_LoadTexture(renderer, "resources/Music.png");
	sfx = IMG_LoadTexture(renderer, "resources/Sound.png");
	border = IMG_LoadTexture(renderer, "resources/border.png");
	shop_but = IMG_LoadTexture(renderer, "resources/shop.png");
	shopbgr = IMG_LoadTexture(renderer, "resources/shopbgr.png");
	coin = IMG_LoadTexture(renderer, "resources/coin.png");
	for (int i = 0; i < 2; i++) {
		price[i] = loadTexture(renderer, "resources/price" + to_string(i + 1) + ".png");
		new_player[i] = loadTexture(renderer, "resources/new_player" + to_string(i + 1) + ".png");
		new_player_bul[i] = loadTexture(renderer, "resources/new_playerbul" + to_string(i + 1) + ".png");
		isBought[i] = false;
	}

	start_rect = { SCREEN_WIDTH/2 - 125, 250, 250, 80 };
	rec_but_rect = { SCREEN_WIDTH / 2 - 125, 350, 250, 80 };
	rec_header_rect = { SCREEN_WIDTH / 2 - 100, 370, 200, 40 };
	inf_but_rect = { SCREEN_WIDTH / 2 - 125, 450, 250, 80 };
	inf_header_rect = { SCREEN_WIDTH / 2 - 100, 470, 200, 40 };
	exit_rect = { SCREEN_WIDTH/2 - 125, 550, 250, 80 };
	mode1P_rect = { SCREEN_WIDTH / 2 - 250 - 50, SCREEN_HEIGHT / 2 - 40, 250, 80 };
	mode2P_rect = { SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 40, 250, 80 };
	back_rect = { 10, 10 , 50, 50 };
	pauseheader_rect = { SCREEN_WIDTH / 2 - 150, 110, 300, 50 };
	pausewindow_rect = { SCREEN_WIDTH / 2 - 200, 100, 400, 500 };
	replay_rect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50, 100, 100 };
	game_quit_rect = { SCREEN_WIDTH / 2 - 50 + 110, SCREEN_HEIGHT / 2 - 50, 100, 100 };
	game_continue_rect = { SCREEN_WIDTH / 2 - 50 - 110, SCREEN_HEIGHT / 2 - 50, 100, 100 };
	pause_rect = { SCREEN_WIDTH - 120, 5, 50, 50 };
	sound_rect = { SCREEN_WIDTH - 60, 5, 50, 50 };
	set_but_rect = { 10, SCREEN_HEIGHT - 70, 50, 50 };
	shop_but_rect = { 70, SCREEN_HEIGHT - 70, 50, 50 };
	setting_rect = { SCREEN_WIDTH/2 - 400, SCREEN_HEIGHT/2 - 150, 800, 300 };
	gfx_rect = { SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - 120, 150, 30 };
	gfx_control = { SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - 80, 600, 50 };
	sfx_rect = { SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - 10, 150, 30 };
	sfx_control = { SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 + 30, 600, 50 };
	border_rect1 = { SCREEN_WIDTH / 2 - 303, SCREEN_HEIGHT / 2 - 83, 606, 56 };
	border_rect2 = { SCREEN_WIDTH / 2 - 303, SCREEN_HEIGHT / 2 + 27, 606, 56 };
	shop_window_rect = { SCREEN_WIDTH / 2 - 200, 50, 400, 500 };
	coin_rect1 = { SCREEN_WIDTH / 2 + 450, 5, 40, 40 };
	coin_rect2 = {SCREEN_WIDTH/2 - 150, 60, 50, 50};
	shop_item[0] = { SCREEN_WIDTH / 2 - 150, 150, 60, 60 };
	shop_item[1] = { SCREEN_WIDTH/2 - 150, 250, 60, 60 };
	shop_item[2] = { SCREEN_WIDTH/2 - 150, 350, 60, 60 };
	price_rect[0] = {SCREEN_WIDTH / 2 - 50, 260, 100, 40};
	price_rect[1] = {SCREEN_WIDTH / 2 - 50, 360, 100, 40};
}
void game::loadText() {
	Score.initText("font/Koulen-Regular.ttf");
	Round.initText("font/Koulen-Regular.ttf");
	GameOver1.initText("font/Koulen-Regular.ttf");
	GameOver2.initText("font/Koulen-Regular.ttf");
	Money.initText("font/Koulen-Regular.ttf");
	DisPlayFps.initText("font/Koulen-Regular.ttf");
	rate.initText("font/Koulen-Regular.ttf");
	money_sum.initText("font/Koulen-Regular.ttf");
}
void game :: loadSound() {
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	cover = Mix_LoadMUS("sound/Levels-Avicii.mp3");
	p_shot1 = Mix_LoadWAV("sound/p_shot1.ogg");
	chunk[0] = p_shot1;
	p_shot2 = Mix_LoadWAV("sound/p_shot2.wav");
	chunk[1] = p_shot2;
	explo_sound = Mix_LoadWAV("sound/explo_sound.ogg");
	chunk[2] = explo_sound;
	asteroid = Mix_LoadWAV("sound/asteroid.wav");
	chunk[3] = asteroid;
	shield_hit = Mix_LoadWAV("sound/shield_hit.wav");
	chunk[4] = shield_hit;
	picked = Mix_LoadWAV("sound/picked.wav");
	chunk[5] = picked;
	skillE = Mix_LoadWAV("sound/skillE.wav");
	chunk[6] = skillE;
	skillQ = Mix_LoadWAV("sound/skillQ.wav");
	chunk[7] = skillQ;
	Mix_PlayMusic(cover, -1);
	Mix_VolumeMusic(30);
	Mix_VolumeChunk(explo_sound, 30);
	Mix_VolumeChunk(p_shot1, 50);
	Mix_VolumeChunk(p_shot2, 50);
}

void game :: loadDefault() {
	type = rand() % 2 + 1;
	for (int i = 0; i < 3; i++) {
		bgr[i] = loadTexture(renderer, "resources/bgr" + to_string(i + 1) + ".png");
	}
	scorebar = IMG_LoadTexture(renderer, "resources/scorebar.png");
	explo = IMG_LoadTexture(renderer, "resources/explosion2.png");
	gameover = IMG_LoadTexture(renderer, "resources/gameover.png");
	life_bar = IMG_LoadTexture(renderer, "resources/lifebar.png");
	energy = IMG_LoadTexture(renderer, "resources/energy.png");
	scorebar_rect = { 0, 0, SCREEN_WIDTH, 60 };
	lifebar_rect = { 200, 0, 140, 60 };
	energy_rect = { 160, 0, 40, 60 };
	bgr_rect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	explo_rect;
}

void game::loadShield (){
		shield_pickup = IMG_LoadTexture(renderer, "resources/shield_pickup.png");
		shield = IMG_LoadTexture(renderer, "resources/Shield.png");
		shield_rect;
		shieldpickup_rect;
}

void game::loadAsteroid() {
	f_asteroid = IMG_LoadTexture(renderer, "resources/asteroid_fly.png");
	d_astoroid = IMG_LoadTexture(renderer, "resources/asteroid_destroy.png");
	f_asteroid_rect;
	d_asteroid_rect;
}

void game::loadHeal() {
	heal_pickup = IMG_LoadTexture(renderer, "resources/heal_pickup.png");
	heal_rect;
}

void game::Resetgame() {
	score = 0;
	coin_cnt = 0;
	level = 1;
	check = true;
	cnt = 0;
	curframe_ex = 0;
	curframe_blood = 0;
	curframe_energy = 10;
	explo_rect = { 0, 0, 0, 0 };

	curframe_shield = 0;
	isShield = false;
	shield_wait.Reset();
	shield_time.Reset();
	Shield.Reset();
	shieldpickup_rect = { 0,0,0,0 };
	shield_rect = { 0,0,0, 0};

	curframe_asteroid = 7;
	isDes = false;
	asteroid_wait.Reset();
	x_start = SCREEN_WIDTH - 300;
	angle = 0;
	wait_time = rand() % 10000 + 5000;
	d_asteroid_rect = { 0, 0, 0, 0 };
	f_asteroid_rect = { 0, 0, 0, 0 };

	curframe_heal = 0;
	isHeal = false;
	heal_wait.Reset();
	heal_time.Reset();
	heal_rect = { 0, 0, 0, 0 };

	highscore.close();
	
	SDL_RenderClear(renderer);
}

void game::loadCharacter() {
	for (int i = 0; i < 2; i++) {
		p_shot[i] = loadTexture(renderer, "resources/playerbullet" + to_string(i + 1) + ".png");
		e_flame[i] = loadTexture(renderer, "resources/e_flame" + to_string(i + 1) + ".png");
	}

	for (int i = 0; i < 3; i++) {
		p_img[i] = loadTexture(renderer, "resources/player" + to_string(i + 1) + ".png");
		creep_bul[i] = loadTexture(renderer, "resources/creepbul" + to_string(i + 1) + ".png");
		boss_bul[i] = loadTexture(renderer, "resources/bossbul" + to_string(i + 1) + ".png");
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			creep[i][j] = loadTexture(renderer, "resources/creep" + to_string(i + 1) + to_string(j + 1) + ".png");
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			boss[i][j] = loadTexture(renderer, "resources/boss" + to_string(i + 1) + to_string(j + 1) + ".png");
		}
	}
	p_engine = loadTexture(renderer, "resources/engine_boost.png");
	p_sup = loadTexture(renderer, "resources/support1.png");
	p_sup_bul = loadTexture(renderer, "resources/supportbul1.png");
	mouse_img = loadTexture(renderer, "resources/setCursor.png");
}

void game::loadSingleGame(player& astro1, vector<enemy>& list_creep, enemy& Boss) {
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

		//render and update astro by time
		updatePlayer(astro1, list_creep);

		// render score text
		Score.setText("Score: " + to_string(score));
		Score.createaText(renderer);

		// render money text
		Money.setText(to_string(coin_cnt));
		Money.createaText(renderer);

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

		// end game
		if (astro1.isKilled()) {
			SDL_ShowCursor(SDL_ENABLE); // show cursor when game over 
			Mix_PlayChannel(-1, explo_sound, 0);
			// open highscore and money to update
			highscore.open("highscore.txt", ios::app);
			highscore << " " << score;
			money.open("coin.txt", ios::in);
			money >> coin_sum;
			money.close();
			money.open("coin.txt", ios::out);
			coin_sum += coin_cnt;
			money << coin_sum;

			highscore.close();
			money.close();

			SDL_RenderCopy(renderer, gameover, NULL, NULL);
			GameOver1.setText("YOUR SCORE: " + to_string(score));
			GameOver1.createaText(renderer);

			while (!quit && isChoose) {
				if (SDL_PollEvent(&event) != 0) {
					if (event.type == SDL_QUIT) {
						quit = true;
					}
				}
				renderMenuGameOver();
			}
			break;
		}
		handleMute();
		SDL_SetTextureColorMod(bgr[type - 1], 255, 255, 255);

		// render FPS text
		DisPlayFps.setText(to_string(frame_rate));
		DisPlayFps.createaText(renderer);

		SDL_RenderPresent(renderer);

		// check frame
		if (frame.GetTime() < 1000 / FPS) {
			SDL_Delay(1000 / FPS - frame.GetTime());
		}
		frame_rate = 1000 / frame.GetTime();
	}
}

void game::load2Playergame(player& astro1, player& astro2) {
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

		// end game
		if (astro1.isKilled() || astro2.isKilled()) {
			Mix_PlayChannel(-1, explo_sound, 0);
			SDL_RenderCopy(renderer, gameover, NULL, NULL);
			if (astro2.isKilled()) {
				GameOver2.setText("PLAYER 1 WIN");
				GameOver2.createaText(renderer);
			}
			else {
				GameOver2.setText("PLAYER 2 WIN");
				GameOver2.createaText(renderer);
			}
			while (!quit && isChoose) {
				if (SDL_PollEvent(&event) != 0) {
					if (event.type == SDL_QUIT) {
						quit = true;
					}
				}
				renderMenuGameOver();
			}
			break;
		}

		handleMute();
		SDL_RenderPresent(renderer);
	}
}

