#include "rendergame.h"

// scale of the window
float scaleX = 1.0;
float scaleY = 1.0;

// log error
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
    // if init SDL fail
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError("SDL_ Init", true);
	}

    // create window
	window = SDL_CreateWindow("WARCRAFT", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // if create window fail
	if (window == nullptr) {
		logSDLError("CreatWindow", true);
	}

    // create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // if create renderer fail
	if (renderer == nullptr) {
		logSDLError("CreateRenderer", true);
	}

    // set scaling of renderer quality to linear
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    // set renderer size depends on the window size
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
    return (a.y >= b.y - 20 && a.y <= b.y + b.h);
}

bool RD::checkCrash(SDL_Rect a, SDL_Rect b) {
    if (checkCollision(a, b) && a.x + a.w <= b.x + 5 && checkSeen(a,b)) return true;
    return false;
}

// load texture
SDL_Texture* RD::loadTexture(SDL_Renderer* renderer, string path) {
    SDL_Texture* new_tex;
    new_tex = IMG_LoadTexture(renderer, path.c_str());

    return new_tex;
}