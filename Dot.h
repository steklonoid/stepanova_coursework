#pragma once
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

	friend bool operator + (const Dot& x, const Dot& y);
};

Dot operator + (const Dot& dot1, const Dot& dot2)
{
	Dot dot3;
	dot3.x = dot1.x + dot2.x;
	dot3.y = dot1.y + dot2.y;
	return dot3;
}
