#include "Text.h"

Text::Text(int _x, int _y, int _h, int _w, int color)
{
	rect.w = _w;
	rect.h = _h;
	rect.x = _x;
	rect.y = _y;
	setColor(color);
}

Text::~Text()
{
}

void Text::initText(string path)
{
	// if init error
	if (TTF_Init() == -1) {
		cout << "Error load Text" << endl;
	}
	// open and load font
	font_text = TTF_OpenFont(path.c_str(), 100);
	// if load error
	if (font_text == NULL) {
		cout << "Error load Font" << endl;
	}
}

void Text::setColor(const int& type)
{
	if (type == RED) {
		SDL_Color color = { 255,0,0 };
		text_color = color;
	}
	else if (type == WHITE) {
		SDL_Color color = { 255, 255, 255 };
		text_color = color;

	}
	else {
		SDL_Color color = { 127, 255, 212 };
		text_color = color;
	}
}

void Text::createaText(SDL_Renderer* renderer)
{
	// create surface
	textSurface = TTF_RenderText_Solid(font_text, str.c_str(), text_color);
	// change surface to texture to use renderer
	body = SDL_CreateTextureFromSurface(renderer, textSurface);
	show(renderer, NULL);
	// clear to avoid memory leak
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(body);
}
