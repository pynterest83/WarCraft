#include "menu.h"

void renderMenu() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, menu, NULL, NULL);
	SDL_RenderCopy(renderer, start, NULL, &start_rect);
	SDL_RenderCopy(renderer, game_exit, NULL, &exit_rect);
	SDL_RenderCopy(renderer, rec_but, NULL, &rec_but_rect);
	SDL_RenderCopy(renderer, rec_header, NULL, &rec_header_rect);
	SDL_RenderCopy(renderer, inf_but, NULL, &inf_but_rect);
	SDL_RenderCopy(renderer, info_header, NULL, &inf_header_rect);
	SDL_RenderCopy(renderer, set_but, NULL, &set_but_rect);
	SDL_RenderCopy(renderer, shop_but, NULL, &shop_but_rect);
	SDL_GetMouseState(&mouse.x, &mouse.y);

	if (SDL_PointInRect(&mouse, &start_rect)) {
		SDL_SetTextureColorMod(start, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			Start = true;
		}
	}
	else SDL_SetTextureColorMod(start, 150, 150, 150);

	if (SDL_PointInRect(&mouse, &exit_rect)) {
		SDL_SetTextureColorMod(game_exit, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			quit = true;
		}
	}
	else SDL_SetTextureColorMod(game_exit, 150, 150, 150);

	if (SDL_PointInRect(&mouse, &rec_but_rect)) {
		SDL_SetTextureColorMod(rec_but, 255, 255, 255);
		SDL_SetTextureColorMod(rec_header, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			isHi = true;
		}
	}
	else {
		SDL_SetTextureColorMod(rec_but, 150, 150, 150);
		SDL_SetTextureColorMod(rec_header, 150, 150, 150);
	}

	if (SDL_PointInRect(&mouse, &inf_but_rect)) {
		SDL_SetTextureColorMod(inf_but, 255, 255, 255);
		SDL_SetTextureColorMod(info_header, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			isInf = true;
		}
	}
	else {
		SDL_SetTextureColorMod(inf_but, 150, 150, 150);
		SDL_SetTextureColorMod(info_header, 150, 150, 150);
	}

	if (SDL_PointInRect(&mouse, &set_but_rect)) {
		SDL_SetTextureColorMod(set_but, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			isSet = true;
		}
	}
	else {
		SDL_SetTextureColorMod(set_but, 150, 150, 150);
	}

	if (SDL_PointInRect(&mouse, &shop_but_rect)) {
		SDL_SetTextureColorMod(shop_but, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			isShop = true;
		}
	}
	else {
		SDL_SetTextureColorMod(shop_but, 150, 150, 150);
	}

	SDL_RenderPresent(renderer);
}

void renderMenu2() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, menu, NULL, NULL);
	SDL_RenderCopy(renderer, mode1P, NULL, &mode1P_rect);
	SDL_RenderCopy(renderer, mode2P, NULL, &mode2P_rect);
	SDL_RenderCopy(renderer, back, NULL, &back_rect);
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (SDL_PointInRect(&mouse, &mode1P_rect)) {
		SDL_SetTextureColorMod(mode1P, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			isChoose = true;
			Start = false;
			gametype = 1;
		}
	}
	else SDL_SetTextureColorMod(mode1P, 150, 150, 150);

	if (SDL_PointInRect(&mouse, &mode2P_rect)) {
		SDL_SetTextureColorMod(mode2P, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			isChoose = true;
			Start = false;
			gametype = 2;
		}
	}
	else SDL_SetTextureColorMod(mode2P, 150, 150, 150);

	if (SDL_PointInRect(&mouse, &back_rect)) {
		SDL_SetTextureColorMod(back, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			Start = false;
		}
	}
	else SDL_SetTextureColorMod(back, 150, 150, 150);

	SDL_RenderPresent(renderer);
}

void renderMenuPause() {
	replay_rect = { SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50, 100, 100 };
	game_quit_rect = { SCREEN_WIDTH / 2 - 50 + 110, SCREEN_HEIGHT / 2 - 50, 100, 100 };
	game_continue_rect = { SCREEN_WIDTH / 2 - 50 - 110, SCREEN_HEIGHT / 2 - 50, 100, 100 };
	SDL_RenderCopy(renderer, pausewindow, NULL, &pausewindow_rect);
	SDL_RenderCopy(renderer, pauseheader, NULL, &pauseheader_rect);
	SDL_RenderCopy(renderer, replay, NULL, &replay_rect);
	SDL_RenderCopy(renderer, game_quit, NULL, &game_quit_rect);
	SDL_RenderCopy(renderer, game_continue, NULL, &game_continue_rect);
	SDL_GetMouseState(&mouse.x, &mouse.y);

	if (SDL_PointInRect(&mouse, &replay_rect)) {
		SDL_SetTextureColorMod(replay, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			isChoose = false;
			Start = true;
		}
	}
	else SDL_SetTextureColorMod(replay, 150, 150, 150);

	if (SDL_PointInRect(&mouse, &game_quit_rect)) {
		SDL_SetTextureColorMod(game_quit, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			quit = true;
		}
	}
	else SDL_SetTextureColorMod(game_quit, 150, 150, 150);

	if (SDL_PointInRect(&mouse, &game_continue_rect)) {
		SDL_SetTextureColorMod(game_continue, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			Pause = false;
		}
	}
	else SDL_SetTextureColorMod(game_continue, 150, 150, 150);

	SDL_RenderPresent(renderer);
}

void renderMenuGameOver() {
	replay_rect = { SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2, 100, 100 };
	game_quit_rect = { SCREEN_WIDTH / 2 + 10, SCREEN_HEIGHT / 2, 100, 100 };
	SDL_RenderCopy(renderer, replay, NULL, &replay_rect);
	SDL_RenderCopy(renderer, game_quit, NULL, &game_quit_rect);
	SDL_GetMouseState(&mouse.x, &mouse.y);

	if (SDL_PointInRect(&mouse, &replay_rect)) {
		SDL_SetTextureColorMod(replay, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			isChoose = false;
			Start = true;
		}
	}
	else SDL_SetTextureColorMod(replay, 150, 150, 150);

	if (SDL_PointInRect(&mouse, &game_quit_rect)) {
		SDL_SetTextureColorMod(game_quit, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			quit = true;
		}
	}
	else SDL_SetTextureColorMod(game_quit, 150, 150, 150);

	SDL_RenderPresent(renderer);
}

void renderMenuHighScore() {
	highscore.open("highscore.txt", ios::in);
	while (highscore) {
		if (highscore) {
			int a;
			highscore >> a;
			rating.push_back(a);
		}
	}
	for (int i = rating.size() - 1; i < 10; i++) {
		rating.push_back(0);
	}
	sort(rating.begin(), rating.end(), greater<int>());

	SDL_RenderCopy(renderer, record, NULL, NULL);
	SDL_RenderCopy(renderer, back, NULL, &back_rect);
	SDL_GetMouseState(&mouse.x, &mouse.y);
	
	if (SDL_PointInRect(&mouse, &back_rect)) {
		SDL_SetTextureColorMod(back, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			isHi = false;
			//highscore.close();
		}
	}
	else SDL_SetTextureColorMod(back, 150, 150, 150);
}

void renderMenuInfo() {
	SDL_RenderCopy(renderer, info, NULL, NULL);
	SDL_RenderCopy(renderer, back, NULL, &back_rect);
	SDL_GetMouseState(&mouse.x, &mouse.y);

	if (SDL_PointInRect(&mouse, &back_rect)) {
		SDL_SetTextureColorMod(back, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			isInf = false;
		}
	}
	else SDL_SetTextureColorMod(back, 150, 150, 150);

	SDL_RenderPresent(renderer);
}

void renderMenuSettings() {
	SDL_RenderCopy(renderer, settings, NULL, NULL);
	SDL_RenderCopy(renderer, back, NULL, &back_rect);
	SDL_RenderCopy(renderer, rec_but, NULL, &setting_rect);
	SDL_SetTextureColorMod(rec_but, 255, 255, 255);
	SDL_RenderCopy(renderer, gfx, NULL, &gfx_rect);
	SDL_RenderCopy(renderer, sfx, NULL, &sfx_rect);
	SDL_RenderCopy(renderer, slider1, NULL, &gfx_control);
	SDL_RenderCopy(renderer, slider2, NULL, &sfx_control);
	SDL_RenderCopy(renderer, border, NULL, &border_rect1);
	SDL_RenderCopy(renderer, border, NULL, &border_rect2);
	SDL_GetMouseState(&mouse.x, &mouse.y);

	if (SDL_PointInRect(&mouse, &back_rect)) {
		SDL_SetTextureColorMod(back, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			isSet = false;
		}
	}
	else SDL_SetTextureColorMod(back, 150, 150, 150);

	if (mouse.x >= SCREEN_WIDTH / 2 - 300 && mouse.x <= SCREEN_WIDTH / 2 + 300 && mouse.y >= SCREEN_HEIGHT / 2 + 30 && mouse.y <= SCREEN_HEIGHT + 80) {
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			sfx_control.w = mouse.x - (SCREEN_WIDTH / 2 - 300);
			for (int i = 0; i < 8; i++) {
				if (i == 2) Mix_VolumeChunk(chunk[i], (sfx_control.w) * 30 * 1.0 / 600);
				else if (i == 0 || i == 1) Mix_VolumeChunk(chunk[i], (sfx_control.w) * 50 * 1.0 / 600);
				else Mix_VolumeChunk(chunk[i], (sfx_control.w) * 128 * 1.0 / 600);
			}
		}
	}

	else if (mouse.x >= SCREEN_WIDTH / 2 - 300 && mouse.x <= SCREEN_WIDTH / 2 + 300 && mouse.y >= SCREEN_HEIGHT / 2 - 80 && mouse.y <= SCREEN_HEIGHT - 30) {
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			gfx_control.w = mouse.x - (SCREEN_WIDTH / 2 - 300);
			Mix_VolumeMusic((gfx_control.w) * 30 * 1.0 / 600);
		}
	}

	SDL_RenderCopy(renderer, slider1, NULL, &gfx_control);
	SDL_RenderCopy(renderer, slider2, NULL, &sfx_control);
	SDL_RenderPresent(renderer);
}

void renderMenuShop() {
	SDL_RenderCopy(renderer, shopbgr, NULL, NULL);
	SDL_RenderCopy(renderer, back, NULL, &back_rect);
	SDL_GetMouseState(&mouse.x, &mouse.y);

	if (SDL_PointInRect(&mouse, &back_rect)) {
		SDL_SetTextureColorMod(back, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			isShop = false;
		}
	}
	else SDL_SetTextureColorMod(back, 150, 150, 150);

	SDL_RenderPresent(renderer);
}