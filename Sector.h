#pragma once
#include "Ñircle.h"

class Sector: public Circle
{
protected:
	float a, b;

public:
	Sector()
	{
		a = b = 0;
	}
	Sector(float _x, float _y, float _rad, float _a, float _b): Circle(_x, _y, _rad), a(_a), b(_b)
	{
	}
	~Sector(){}

	float geta() { return a; }
	void seta(float _a) { a = _a; }
	float getb() { return b; }
	void setb(float _b) { b = _b; }


};


