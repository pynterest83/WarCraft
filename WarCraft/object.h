#pragma once

#include "rendergame.h"

class object {
protected:
    SDL_Rect rect;
    SDL_Texture* body;
public:
    object();
    ~object();
    void show (SDL_Renderer* renderer);
    void setImg (SDL_Renderer* renderer, string path);
    void setPos (int x, int y);
    SDL_Rect getRect() const {
		return rect;
	}
    void Animation();
};