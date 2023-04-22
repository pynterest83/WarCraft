#include "object.h"

object::object(){
    // default feature of object
    rect.x;
    rect.y;
    rect.h;
    rect.w;
    body=NULL;
}

object::~object(){

}

void object::show(SDL_Renderer* renderer, SDL_Rect* clip) {
    // show object depends on the size of source clip
    SDL_RenderCopy(renderer, body, clip, &rect);
    // if show failed
    if (renderer == NULL) {
        cout << "show failed" << endl;
    }
}

void object::setImg(SDL_Texture* p_tex){
    // body of object is the p_tex
    body = p_tex;
}

void object::setPos(int x, int y){
    // set position of object
    // x, y is the position of object
    rect.x=x;
    rect.y=y;
}