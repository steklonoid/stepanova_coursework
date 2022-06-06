#pragma once
#include "Dot.h"

class Circle: public Dot
{
protected:
	float rad;

public:
	Circle()
	{
		rad = 0;
	}
	Circle(float _x, float _y, float _rad): Dot(_x, _y), rad(_rad)
	{
	}
	~Circle() {}

	float getrad() { return rad; }
	void setrad(float _rad) { rad = _rad; }
};

