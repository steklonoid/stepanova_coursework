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
};