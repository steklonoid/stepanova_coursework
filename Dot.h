#pragma once
#include <string>
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
	Dot dot1;
	out << "x: " << dot1.getx() << " y: " << dot1.gety() << "\n";
	return out;
}
istream& operator>> (istream& in, Dot& dot)
{
	string bebebe;
	cout << "Enter x: ";
	getline(in, bebebe);
	dot.x = stof(bebebe);

	string be;
	cout << "Enter y: ";
	getline(in, be);
	dot.y = stof(be);
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