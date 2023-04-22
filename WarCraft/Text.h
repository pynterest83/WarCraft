#pragma once

#include "Object.h"

class Text : public object {
	// content of text to show
	string str;
	// color of text
	SDL_Color text_color;
	SDL_Surface* textSurface;

public:
	// 3 popular color
	enum TextColor {
		RED = 0,
		WHITE = 1,
		Aquamarine = 2
	};
	// set position and text color
	Text(int _x, int _y, int _h, int _w, int color);
	~Text();
	// load font
	void initText(TTF_Font*& fontText, string path);
	// set str = text
	void setText(string text) { str = text; }
	// set some default color to choose
	void setColor(const int& type);
	// create text
	void createaText(TTF_Font* font, SDL_Renderer* renderer);
};