#pragma once

#include "object.h"

class ebullet: public object{
private:
	int x;
	int y;
	bool isMove;
	int speed;
public:
	int r = 0;
	int start_x, start_y;
	bool isBouncing1 = false;
	bool isBouncing2 = false;
	bool isBouncing3 = false;
	bool isBouncing4 = false;
	ebullet();
	~ebullet();
	void fire(double direct, int type);
	void bossfire(int i, double direct, int typeshot);
	void spfire(double direct);
	void bouncefire(double direct);
	void bounce1(double direct);
	void bounce2(double direct);
	void bounce3(double direct);
	void bounce4(double direct);
	// set staus of bullet to false to stop or bouncing it
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