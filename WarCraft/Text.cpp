#include "Text.h"

Text::Text()
{
	rect.w = 100;
	rect.h = 50;
	rect.x = 5;
	rect.y = 5;
	setColor(1);
}

Text::~Text()
{
}

void Text::initText(TTF_Font*& fontText)
{
	if (TTF_Init() == -10) {
		cout << "Loi Text" << endl;
	}
	fontText = TTF_OpenFont("E:/personal/Code/C++/LTNC/GameSDL2/WarCraft/WarCraft//Koulen-Regular.ttf", 20);
	if (fontText == NULL) {
		cout << "Loi font" << endl;
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

void Text::createaText(TTF_Font* font, SDL_Renderer* renderer)
{
	textSurface = TTF_RenderText_Solid(font, str.c_str(), text_color);
	body = SDL_CreateTextureFromSurface(renderer, textSurface);
	show(renderer);
}
