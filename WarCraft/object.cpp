#include <object.h>

object::object(){
    rect.x;
    rect.y;
    rect.h;
    rect.w;
    body=NULL;
}

object::~object(){

}

void object::show(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, body, NULL, &rect);
}

void object::setImg(SDL_Renderer* renderer, string path){
    body=RD::loadTexture(renderer, path);
    if (body==NULL){
        cout << "fail to load image";
    }
}

void object::setPos(int x, int y){
    rect.x=x;
    rect.y=y;
}