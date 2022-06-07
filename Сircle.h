#pragma once
#include <iostream>
#include <string>
#include "Dot.h"
using namespace std;

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

	friend ostream& operator<< (ostream& out, const Circle& dot);
	friend istream& operator>> (istream& in, Circle& dot);
};

ostream& operator<< (ostream& out, const Circle& rad)
{
	Circle rad1;
	out << "radius: " << rad1.getrad()  << "\n";
	return out;
}
