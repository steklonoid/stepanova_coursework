#pragma once
#include <iostream>
#include <string>
#include "�ircle.h"
using namespace std;
//����������� �� Circle �����
class Sector: public Circle
{
protected:
	float a, b;

public:
	//����������� �� ���������
	Sector();
	//����������� � �����������
	Sector(float _x, float _y, float _rad, float _a, float _b);
	~Sector();//����������
	//������, �������
	float geta();
	void seta(float _a);
	float getb();
	void setb(float _b);
	//����������� ������� �����������
	virtual void moveTo(float _x, float _y) override;
	//������������� ���������
	friend bool operator == (const Sector& sector1, const Sector& sector2);
	friend bool operator != (const Sector& sector1, const Sector& sector2);
	friend ostream& operator<< (ostream& out, const Sector& sector);
	friend istream& operator>> (istream& in, Sector& sector);
};