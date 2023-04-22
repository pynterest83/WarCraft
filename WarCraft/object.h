#pragma once

#include "rendergame.h"

class object {
protected:
    // rect of object
    SDL_Rect rect;
    // texture of object
    SDL_Texture* body;
public:
    object();
    ~object();
    // show object
    void show (SDL_Renderer* renderer, SDL_Rect* Clip);
    // set texture of object
    void setImg (SDL_Texture* p_tex);
    // set position of object
    void setPos (int x, int y);
    // get rect of object to check interaction
    SDL_Rect getRect() const {
		return rect;
	}
};