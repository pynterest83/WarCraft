#include "menu.h"

void renderMenu() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, menu, NULL, NULL);
	SDL_RenderCopy(renderer, start, NULL, &start_rect);
	SDL_RenderCopy(renderer, game_exit, NULL, &exit_rect);
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (SDL_PointInRect(&mouse, &start_rect)) {
		SDL_SetTextureColorMod(start, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.y, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			Start = true;
		}
	}
	else SDL_SetTextureColorMod(start, 150, 150, 150);

	if (SDL_PointInRect(&mouse, &exit_rect)) {
		SDL_SetTextureColorMod(game_exit, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.y, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			quit = true;
		}
	}
	else SDL_SetTextureColorMod(game_exit, 150, 150, 150);

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
		if (SDL_GetMouseState(&mouse.y, &mouse.y) & SDL_BUTTON(1)) {
			isChoose = true;
			Start = false;
			gametype = 1;
		}
	}
	else SDL_SetTextureColorMod(mode1P, 150, 150, 150);

	if (SDL_PointInRect(&mouse, &mode2P_rect)) {
		SDL_SetTextureColorMod(mode2P, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.y, &mouse.y) & SDL_BUTTON(1)) {
			isChoose = true;
			Start = false;
			gametype = 2;
		}
	}
	else SDL_SetTextureColorMod(mode2P, 150, 150, 150);

	if (SDL_PointInRect(&mouse, &back_rect)) {
		SDL_SetTextureColorMod(back, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.y, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			Start = false;
		}
	}
	else SDL_SetTextureColorMod(back, 150, 150, 150);

	SDL_RenderPresent(renderer);
}

void renderMenuPause() {
	SDL_RenderCopy(renderer, pausewindow, NULL, &pausewindow_rect);
	SDL_RenderCopy(renderer, pauseheader, NULL, &pauseheader_rect);
	SDL_RenderCopy(renderer, replay, NULL, &replay_rect);
	SDL_RenderCopy(renderer, game_quit, NULL, &game_quit_rect);
	SDL_RenderCopy(renderer, game_continue, NULL, &game_continue_rect);
	SDL_GetMouseState(&mouse.x, &mouse.y);

	if (SDL_PointInRect(&mouse, &replay_rect)) {
		SDL_SetTextureColorMod(replay, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.y, &mouse.y) & SDL_BUTTON(1)) {
			isChoose = false;
			Start = true;
		}
	}
	else SDL_SetTextureColorMod(replay, 150, 150, 150);

	if (SDL_PointInRect(&mouse, &game_quit_rect)) {
		SDL_SetTextureColorMod(game_quit, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.y, &mouse.y) & SDL_BUTTON(1)) {
			quit = true;
		}
	}
	else SDL_SetTextureColorMod(game_quit, 150, 150, 150);

	if (SDL_PointInRect(&mouse, &game_continue_rect)) {
		SDL_SetTextureColorMod(game_continue, 255, 255, 255);
		if (SDL_GetMouseState(&mouse.y, &mouse.y) & SDL_BUTTON(1)) {
			SDL_Delay(100);
			Pause = false;
		}
	}
	else SDL_SetTextureColorMod(game_continue, 150, 150, 150);

	SDL_RenderPresent(renderer);
}