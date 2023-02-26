#include "rendergame.h"

void RD::logSDLError(const string& msg, bool fatal)
{
	cout << msg << " Error: " << SDL_GetError() << endl;
	if (fatal) {
		SDL_Quit();
		exit(1);
	}
}

void RD::initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError("SDL_ Init", true);
	}

	window = SDL_CreateWindow("CRAFT SHOOTING", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		logSDLError("CreatWindow", true);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) {
		logSDLError("CreateRenderer", true);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void RD::quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool RD::checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool RD::checkSeen(SDL_Rect a, SDL_Rect b) {
    return (b.y <= a.y && b.y >= a.y - a.h);
}

bool RD::checkCrash(SDL_Rect a, SDL_Rect b) {
    if (checkCollision(a, b) && a.x + a.w <= b.x + 5 && checkSeen(a,b)) return true;
    return false;
}