#pragma once

#ifndef RENDERGAME_H
#define RENDERGAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

const int SCREEN_WIDTH=1280;
const int SCREEN_HEIGHT=720;
static TTF_Font* font_text=NULL;

namespace RD {
    void logSDLError(const string& msg, bool fatal);
	void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
	void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	bool checkSeen(SDL_Rect a, SDL_Rect b);
	bool checkCrash(SDL_Rect a, SDL_Rect b);
}

#endif