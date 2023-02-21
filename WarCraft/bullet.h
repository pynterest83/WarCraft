#pragma once

#include "object.h"
class bullet : public object{
private:
	int x;
	int y;
	bool isMove;
	int speed;
public:
	bullet();
	~bullet();
	void fire();
	void setStatus(bool _isMove) {
		isMove = _isMove;
		if (_isMove == false) {
			setPos(rect.x + rect.w / 2, rect.y + rect.h / 2 - 4);
		}
	}
	bool is_Move() { return isMove; }
};