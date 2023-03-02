#pragma once

#include "Object.h"

class Text : public object {
private:
	string str;
	SDL_Color text_color;
	SDL_Surface* textSurface;

public:
	enum TextColor {
		RED = 0,
		WHITE = 1,
		Aquamarine = 2
	};
	Text(int _x, int _y, int _h, int _w, int color);
	~Text();
	void initText(TTF_Font*& fontText, string path);
	void setText(string text) { str = text; }
	void setColor(const int& type);
	void createaText(TTF_Font* font, SDL_Renderer* renderer);
};