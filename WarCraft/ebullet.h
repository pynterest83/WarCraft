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
	void fire();
	void setStatus(bool _isMove) {
		isMove = _isMove;
	}
	bool is_Move() { return isMove; }
};