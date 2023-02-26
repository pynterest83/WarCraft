#pragma once

#include "object.h"

class bossBullet : public object {
private:
	int x;
	int y;
	bool isMove;
	int speed;
public:
	bossBullet();
	~bossBullet();
	void fire(SDL_Rect a, SDL_Rect b);
	void setStatus(bool _isMove) {
		isMove = _isMove;
		if (_isMove == false) {
			setPos(rect.x + rect.w / 2, rect.y + rect.h / 2 - 4);
		}
	}
	bool is_Move() { return isMove; }
};