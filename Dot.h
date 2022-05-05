#pragma once
class Dot
{
protected:
	float x;
	float y;

public:
	Dot()
	{
		x = 0;
		y = 0;
	}
	float get_x() { return x; }
	float get_y() { return y; }
	virtual void moveTo(float _x, float _y)
	{
		x = _x;
		y = _y;
	}


};

