#pragma once

#include "object.h"

class ebullet: public object{
private:
	int x;
	int y;
	bool isMove;
	int speed;
public:
	ebullet();
	~ebullet();
	void fire(SDL_Rect a, SDL_Rect b);
	void setStatus(bool _isMove) {
		isMove = _isMove;
		if (_isMove == false) {
			setPos(rect.x + rect.w / 2, rect.y + rect.h / 2 - 4);
		}
	}
	bool is_Move() { return isMove; }
	int getSpeed(int _speed) { 
		speed = _speed;
		return speed; 
	}
	void getsize(int w, int h) {
		rect.w = w;
		rect.h = h;
	}
};