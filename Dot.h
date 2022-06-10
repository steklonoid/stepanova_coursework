#pragma once
#include <iostream>
#include <string>
using namespace std;
class Dot
{
protected:	
	float x, y;

public:
	Dot()
	{
		x = y = 0;
	}
	Dot(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	Dot(const Dot& from_dot)
	{
		x = from_dot.x;
		y = from_dot.y;
	}
	~Dot(){}

	float getx() { return x; }
	void setx(float _x) { x = _x; }
	float gety() { return y; }
	void sety(float _y) { y = _y; }

	virtual void moveTo(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	friend Dot operator + (const Dot& dot1, const Dot& dot2);
	friend Dot operator * (const Dot& dot, float koef);
	friend Dot operator - (const Dot& dot1, const Dot& dot2);
	friend Dot operator / (const Dot& dot, float koef);

	friend ostream& operator<< (ostream& out, const Dot& dot);
	friend istream& operator>> (istream& in, Dot& dot);
};

ostream& operator<< (ostream& out, const Dot& dot)
{	
	out << "x: " << dot. x<< " y: " << dot.y << "\n";
	return out;
}
istream& operator>> (istream& in, Dot& dot)
{	
	cout << "Enter x: ";
	cin >> dot.x;	
	cout << "Enter y: ";	
	cin >> dot.y;
	return in;
}

Dot operator + (const Dot& dot1, const Dot& dot2)
{
	Dot dot3;
	dot3.x = dot1.x + dot2.x;
	dot3.y = dot1.y + dot2.y;
	return dot3;
}
Dot operator * (const Dot& dot, float koef)
{
	Dot dot1;
	dot1.x = dot.x * koef;
	dot1.y = dot.y * koef;
	return dot1;
}
Dot operator / (const Dot& dot, float koef)
{
	Dot dot1;
	dot1.x = dot.x / koef;
	dot1.x = dot.x / koef;
	return dot1;
}
Dot operator - (const Dot& dot1, const Dot& dot2)
{
	Dot dot3;
	dot3.x = dot1.x - dot2.x;
	dot3.y = dot1.y - dot2.y;
	return dot3;
}