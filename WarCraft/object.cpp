#include "object.h"

object::object(){
    rect.x;
    rect.y;
    rect.h;
    rect.w;
    body=NULL;
}

object::~object(){

}

void object::show(SDL_Renderer* renderer, SDL_Rect* clip) {
    SDL_RenderCopy(renderer, body, clip, &rect);
    if (renderer == NULL) {
        cout << "show failed" << endl;
    }
}

void object::setImg(SDL_Texture* p_tex){
    body = p_tex;
}

void object::setPos(int x, int y){
    rect.x=x;
    rect.y=y;
}