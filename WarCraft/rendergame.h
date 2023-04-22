#pragma once

#ifndef RENDERGAME_H
#define RENDERGAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <Windows.h>
#include <SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FPS = 65;
extern float scaleX;
extern float scaleY;
static TTF_Font* font_text=NULL;

namespace RD {
	// log error
    void logSDLError(const string& msg, bool fatal);
	// init SDL
	void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
	// quit sdl
	void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

	// check interaction between 2 objects
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	bool checkSeen(SDL_Rect a, SDL_Rect b);
	bool checkCrash(SDL_Rect a, SDL_Rect b);

	// load texture
	SDL_Texture* loadTexture(SDL_Renderer* renderer, string path);
}

#endif