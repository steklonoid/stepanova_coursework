#pragma once
#include "Dot.h"

class Circle: public Dot
{
protected:
	double rad;

public:
	Circle(){}
	~Circle(){}

	float getrad() { return rad; }
	void setrad(double _rad) { rad = _rad; }
};

