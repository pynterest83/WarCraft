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
	Text();
	~Text();
	void initText(TTF_Font*& fontText);
	void setText(string text) { str = text; }
	void setColor(const int& type);
	void createaText(TTF_Font* font, SDL_Renderer* renderer);
};