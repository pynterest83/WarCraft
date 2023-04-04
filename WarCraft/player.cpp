#include "player.h"

player::player() {
	x = rect.w;
	y = SCREEN_HEIGHT / 2;
	rect.w = 60;
	rect.h = 60;
	setPos(x, y);

	if (player_skin == 1) {
		shottype[1].setImg(p_shot[0]);
		shottype[1].setSpeed(10);
	}
	else {
		shottype[1].setImg(new_player_bul);
		shottype[1].setSpeed(10);
	}
	shottype[0].setImg(p_shot[1]);
	shottype[0].setSpeed(25);
	num_bullet = 40;
	turn = 0;
	damage = 1;
	for (int i = 0; i < num_bullet; i++) {
		shot[i] = shottype[0];
	}

	SupIsSet = false;
	supporter.setSp();

	backSpace = true;
	isSkilledQ = false;
	isSkilledR = false;
	skill_wait.Start();
	
	speed = 5;
	blood = 50;
	alive = true;

	engine = e_flame[1];
	engine_boost = p_engine;
	en_frame = 0;
}

void player::move() {
	if (alive) {
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
	blood-=dmg;
	if (blood <= 0) {
		alive = false;
	}
}

void player::handleBullet(SDL_Event event) {
	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
			case SDLK_SPACE: {
				backSpace = true;
			}
			break;
		}
	}
	if (state[SDL_SCANCODE_SPACE] && backSpace) {
		if (turn == 0) Mix_PlayChannel(-1, p_shot1, 0);
		else Mix_PlayChannel(-1, p_shot2, 0);
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
		else if (isSkilledQ) {
			if (skill_time.GetTime() < (Uint32)15000) {
				for (int i = 0; i < num_bullet; i += 2) {
					if (!shot[i].is_Move()) {
						shot[i].setPos(rect.x + rect.w, rect.y + rect.h / 3 - shot[i].getRect().h / 2);
						shot[i + 1].setPos(rect.x + rect.w, rect.y + 2 * rect.h / 3 - shot[i + 1].getRect().h / 2);
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

	if (isSkilledR) {
		if (skill_time.GetTime() >= (Uint32)15000) {
			SupIsSet = false;
			isSkilledR = false;
			skill_time.Pause();
			skill_time.Reset();
			skill_wait.Start();
		}
	}

	if (state[SDL_SCANCODE_E]) {
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
	if (state[SDL_SCANCODE_Q] && skill_wait.GetTime() >= (Uint32)15000) {
		Mix_PlayChannel(-1, skillQ, 0);
		skill_wait.Reset();
		skill_time.Start();
		isSkilledQ = true;
	}
	if (state[SDL_SCANCODE_R] && skill_wait.GetTime() >= (Uint32)15000) {
		isSkilledR = true;
		skill_wait.Reset();
		skill_time.Start();
	}
}

void player::update(SDL_Renderer* renderer, double direct)
{
	if (alive)
	{
		if (player_skin == 1) {
			if (blood >= 35) body = p_img[0];
			else if (blood >= 10) body = p_img[1];
			else if (blood < 10) body = p_img[2];
		}
		else {
			body = new_player;
		}
		show(renderer, NULL);

		SDL_Rect e_boost = { rect.x - 30, rect.y - 20, 100, 100 };
		SDL_Rect e_source = { 0, en_frame * 48, 48, 48 };
		SDL_Rect e_des = { rect.x - 55, rect.y - 22, 200 ,100 };
		SDL_RenderCopy(renderer, engine_boost, NULL, &e_boost);
		SDL_RenderCopy(renderer, engine, &e_source, &e_des);
		en_frame++;
		en_frame = en_frame % 7;
		
		for (int i = 0; i < num_bullet; i++) {
			if (shot[i].is_Move()) {
				shot[i].fire();
				shot[i].show(renderer, NULL);
			}
		}

		if (isSkilledR){
			SDL_GetMouseState(&mouse.x, &mouse.y);
			if (!SupIsSet) {
				SDL_ShowCursor(SDL_DISABLE);
				SDL_Rect mouse_rect = { mouse.x, mouse.y, 50, 50 };
				SDL_RenderCopy(renderer, mouse_img, NULL, &mouse_rect);
			}
			if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1) && !SupIsSet) {
				supporter.setPos(mouse.x, mouse.y);
				SupIsSet = true;
				SDL_ShowCursor(SDL_ENABLE);
				supporter.spautoshot();
			}
			if (SupIsSet) {
				supporter.update(renderer, direct);
			}
		}
	}
	//else SDL_DestroyTexture(body);
}

SDL_Rect player::getRectBullet(int i)
{
	return shot[i].getRect();
}

void player::setP2() {
	setImg(creep[1][0]);

	x = SCREEN_WIDTH - rect.w;
	y = SCREEN_HEIGHT / 2;
	rect.w = 60;
	rect.h = 60;
	setPos(x, y);

	engine = e_flame[0];
}

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
	else SDL_DestroyTexture(body);
}