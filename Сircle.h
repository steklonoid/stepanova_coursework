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

	virtual void moveTo(float _x, float _y) override
	{
		x = _x;
		y = _y;
	}

	friend ostream& operator<< (ostream& out, const Circle& dot);
	friend istream& operator>> (istream& in, Circle& dot);
};

ostream& operator<< (ostream& out, const Circle& circle)
{	
	out << "x: " << circle.x << " y: " << circle.y << " radius: " << circle.rad << "\n";
	return out;
}

istream& operator>> (istream& in, Circle& circle)
{	
	cout << "Enter x: ";
	cin >>	circle.x;
	cout << "Enter y: ";
	cin >> circle.y;
	cout << "Enter radius: ";
	cin >> circle.rad;
	return in;
}
