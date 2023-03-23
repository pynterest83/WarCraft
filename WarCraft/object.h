#pragma once

#include "rendergame.h"

class object {
protected:
    SDL_Rect rect;
    SDL_Texture* body;
public:
    object();
    ~object();
    void show (SDL_Renderer* renderer, SDL_Rect* Clip);
    void setImg (SDL_Texture* p_tex);
    void setPos (int x, int y);
    SDL_Rect getRect() const {
		return rect;
	}
};