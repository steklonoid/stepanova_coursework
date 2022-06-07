#pragma once
#include <iostream>
#include <string>
#include "Ñircle.h"
using namespace std;

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


	friend ostream& operator<< (ostream& out, const Dot& dot);
	friend istream& operator>> (istream& in, Dot& dot);
};

ostream& operator<< (ostream& out, const Sector& sector)
{
	Sector sector1;
	out << "a: " << sector1.geta() << " b: " << sector1.getb() << "\n";
	return out;
}

