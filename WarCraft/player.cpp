#include "player.h"

player::player() {
	// set player position and size
	x = rect.w;
	y = SCREEN_HEIGHT / 2;
	rect.w = 60;
	rect.h = 60;
	setPos(x, y);

	// player skin depends on what player choose in shop
	if (player_skin == 1) {
		shottype[1].setImg(p_shot[0]);
		shottype[1].setSpeed(10);
	}
	else if (player_skin == 2){
		shottype[1].setImg(new_player_bul[0]);
		shottype[1].setSpeed(10);
	}
	else {
		shottype[1].setImg(new_player_bul[1]);
		shottype[1].setSpeed(10);
	}

	// set bullet type img and speed
	shottype[0].setImg(p_shot[1]);
	shottype[0].setSpeed(25);
	num_bullet = 40;
	// default type = 0, default damage = 1
	turn = 0;
	damage = 1;
	for (int i = 0; i < num_bullet; i++) {
		shot[i] = shottype[0];
	}

	// set supporter
	SupIsSet = false;
	supporter.setSp();

	// set space up to shoot
	backSpace = true;
	
	// set skill
	isSkilledQ = false;
	isSkilledR = false;
	skill_wait.Start();
	
	// set speed, blood
	speed = 5;
	blood = 50;
	alive = true;

	// set player skin
	engine = e_flame[1];
	engine_boost = p_engine;
	en_frame = 0;
}

void player::move() {
	if (alive) {
		// player 1 move by AWSD
		if (!isP2) {
			if (rect.x < SCREEN_WIDTH - rect.w && (state[SDL_SCANCODE_D])) {
				rect.x += speed;
			}
			if (rect.x - speed > 0 && (state[SDL_SCANCODE_A])) {
				rect.x -= speed;
			}
			if (rect.y - speed > 60 && (state[SDL_SCANCODE_W])) {
				rect.y -= speed;
			}
			if (rect.y < SCREEN_HEIGHT - rect.h && (state[SDL_SCANCODE_S])) {
				rect.y += speed;
			}
		}
		// player 2 move by IJKL
		else {
			if (rect.x < SCREEN_WIDTH - rect.w && (state[SDL_SCANCODE_L])) {
				rect.x += speed;
			}
			if (rect.x - speed > 0 && (state[SDL_SCANCODE_J])) {
				rect.x -= speed;
			}
			if (rect.y - speed > 60 && (state[SDL_SCANCODE_I])) {
				rect.y -= speed;
			}
			if (rect.y < SCREEN_HEIGHT - rect.h && (state[SDL_SCANCODE_K])) {
				rect.y += speed;
			}
		}
	}
}

player::~player() {

}

void player::kill(int dmg) {
	// decrease damage and check if player is alive
	blood-=dmg;
	if (blood <= 0) {
		alive = false;
	}
}

void player::handleBullet(SDL_Event event) {
	// if space is up, player can shoot
	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
			case SDLK_SPACE: {
				backSpace = true;
			}
			break;
		}
	}
	// if space is up, player can shoot by press space
	if (state[SDL_SCANCODE_SPACE] && backSpace) {
		// play shooting sound depends on bullet type
		if (turn == 0) Mix_PlayChannel(-1, p_shot1, 0);
		else Mix_PlayChannel(-1, p_shot2, 0);
		// if player is not skilled Q, player can only shoot 1 bullet
		if (!isSkilledQ) {
			for (int i = 0; i < num_bullet; i++) {
				if (!shot[i].is_Move()) {
					shot[i].setPos(rect.x + rect.w, rect.y + rect.h / 2 - shot[i].getRect().h / 2);
					shot[i].setStatus(true);
					backSpace = false;
					break;
				}
			}
		}
		// if player is skilled Q, player can shoot 2 bullets
		else if (isSkilledQ) {
			// if skill time is less than 15s, player can shoot 2 bullets
			if (skill_time.GetTime() < (Uint32)15000) {
				for (int i = 0; i < num_bullet; i += 2) {
					if (!shot[i].is_Move()) {
						// set 2 bullet position i and i+1
						shot[i].setPos(rect.x + rect.w, rect.y + rect.h / 3 - shot[i].getRect().h / 2);
						shot[i + 1].setPos(rect.x + rect.w, rect.y + 2 * rect.h / 3 - shot[i + 1].getRect().h / 2);
						shot[i].setStatus(true);
						shot[i + 1].setStatus(true);
						backSpace = false;
						break;
					}
				}
			}
			// off skill, reset all
			else {
				isSkilledQ = false;
				skill_time.Pause();
				skill_time.Reset();
				skill_wait.Start();
			}
		}
	}
	
	if (isSkilledR) {
		// off skill R, reset all
		if (skill_time.GetTime() >= (Uint32)15000) {
			SupIsSet = false;
			isSkilledR = false;
			SDL_ShowCursor(SDL_ENABLE); // if not set, show again the default cursor
			skill_time.Pause();
			skill_time.Reset();
			skill_wait.Start();
		}
	}

	// change bullet type by E
	if (state[SDL_SCANCODE_E]) {
		// play sound
		Mix_PlayChannel(-1, skillE, 0);
		// change bullet type for all bullets in range
		for (int i = 0; i < num_bullet; i++) {
			shot[i] = shottype[1 - turn];
		}
		// reset damage and turn
		// turn is bullet type
		damage = 4 - damage;
		turn = 1 - turn;
	}
	// if skill wait time is more than 15s, player can use skill
	if (skill_wait.GetTime() >= (Uint32)15000) {
		skill_wait.Pause();
	}
	// use skill Q and reset skill wait time
	if (state[SDL_SCANCODE_Q] && skill_wait.GetTime() >= (Uint32)15000) {
		Mix_PlayChannel(-1, skillQ, 0);
		skill_wait.Reset();
		skill_time.Start();
		isSkilledQ = true;
	}
	// use skill R and reset skill wait time
	if (state[SDL_SCANCODE_R] && skill_wait.GetTime() >= (Uint32)15000) {
		isSkilledR = true;
		skill_wait.Reset();
		skill_time.Start();
	}
}

// update player status
void player::update(SDL_Renderer* renderer, double direct)
{
	if (alive)
	{
		// set img depends on player skin
		if (player_skin == 1) {
			if (blood >= 35) body = p_img[0];
			else if (blood >= 10) body = p_img[1];
			else if (blood < 10) body = p_img[2];
		}
		else if (player_skin == 2){
			body = new_player[0];
		}
		else {
			body = new_player[1];
		}
		show(renderer, NULL);

		// set engine effect
		SDL_Rect e_boost = { rect.x - 30, rect.y - 20, 100, 100 };
		SDL_Rect e_source = { 0, en_frame * 48, 48, 48 };
		SDL_Rect e_des = { rect.x - 55, rect.y - 22, 200 ,100 };
		SDL_RenderCopy(renderer, engine_boost, NULL, &e_boost);
		SDL_RenderCopy(renderer, engine, &e_source, &e_des);
		en_frame++;
		en_frame = en_frame % 7;
		
		// show shotted bullet
		for (int i = 0; i < num_bullet; i++) {
			if (shot[i].is_Move()) {
				shot[i].fire();
				shot[i].show(renderer, NULL);
			}
		}

		// set supporter
		if (isSkilledR && gametype == 1){
			// use mouse to set supporter position
			SDL_GetMouseState(&mouse.x, &mouse.y);
			if (!SupIsSet) {
				SDL_ShowCursor(SDL_DISABLE);
				SDL_Rect mouse_rect = { mouse.x, mouse.y, 50, 50 };
				SDL_RenderCopy(renderer, mouse_img, NULL, &mouse_rect);
			}
			// if mouse is clicked, set supporter position
			if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1) && !SupIsSet) {
				supporter.setPos(mouse.x, mouse.y);
				SupIsSet = true;
				SDL_ShowCursor(SDL_ENABLE);
				supporter.spautoshot();
			}
			// if supporter is set, update supporter
			if (SupIsSet) {
				supporter.update(renderer, direct);
			}
		}
	}
}
// get bullet rect to check interaction
SDL_Rect player::getRectBullet(int i)
{
	return shot[i].getRect();
}

// set player2
void player::setP2() {
	setImg(creep[1][0]);

	x = SCREEN_WIDTH - rect.w;
	y = SCREEN_HEIGHT / 2;
	rect.w = 60;
	rect.h = 60;
	setPos(x, y);

	engine = e_flame[0];
}

// handle player2 bullet like player 1 but use POU
void player::P2HandleBullet(SDL_Event event) {
	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_p: {
			backSpace = true;
			}
			break;
		}
	}
	if (state[SDL_SCANCODE_P] && backSpace) {
		if (turn == 0) Mix_PlayChannel(-1, p_shot1, 0);
		else Mix_PlayChannel(-1, p_shot2, 0);
		if (!isSkilledQ) {
			for (int i = 0; i < num_bullet; i++) {
				if (!shot[i].is_Move()) {
					shot[i].setPos(rect.x, rect.y + rect.h / 2 - shot[i].getRect().h / 2);
					shot[i].setStatus(true);
					backSpace = false;
					break;
				}
			}
		}
		else {
			if (skill_time.GetTime() < (Uint32)15000) {
				for (int i = 0; i < num_bullet; i += 2) {
					if (!shot[i].is_Move()) {
						shot[i].setPos(rect.x, rect.y + rect.h / 3 - shot[i].getRect().h / 2);
						shot[i + 1].setPos(rect.x, rect.y + 2 * rect.h / 3 - shot[i + 1].getRect().h / 2);
						shot[i].setStatus(true);
						shot[i + 1].setStatus(true);
						backSpace = false;
						break;
					}
				}
			}
			else {
				isSkilledQ = false;
				skill_time.Pause();
				skill_time.Reset();
				skill_wait.Start();
			}
		}
	}
	if (state[SDL_SCANCODE_O]) {
		Mix_PlayChannel(-1, skillE, 0);
		for (int i = 0; i < num_bullet; i++) {
			shot[i] = shottype[1 - turn];
		}
		damage = 4 - damage;
		turn = 1 - turn;
	}
	if (skill_wait.GetTime() >= (Uint32)15000) {
		skill_wait.Pause();
	}
	if (state[SDL_SCANCODE_U] && skill_wait.GetTime() >= (Uint32)15000) {
		Mix_PlayChannel(-1, skillQ, 0);
		skill_wait.Reset();
		skill_time.Start();
		isSkilledQ = true;
	}
}

// update player2
void player::P2update(SDL_Renderer* renderer) {
	if (alive)
	{
		show(renderer, NULL);

		SDL_Rect e_source = { 0, en_frame * 128, 128, 128 };
		SDL_Rect e_des = { rect.x - 120, rect.y - 25, 200 ,100 };
		SDL_RenderCopy(renderer, engine, &e_source, &e_des);
		en_frame++;
		en_frame = en_frame % 8;

		for (int i = 0; i < num_bullet; i++) {
			if (shot[i].is_Move()) {
				shot[i].p2fire();
				shot[i].show(renderer, NULL);
			}
		}
	}
}