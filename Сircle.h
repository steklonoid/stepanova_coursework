#pragma once
#include <iostream>
#include <string>
#include "Dot.h"
using namespace std;
// ����������� �� Dot �����
class Circle: public Dot
{
protected:
	float rad;

public:
	// ����������� �� ���������
	Circle();
	// ����������� � �����������
	Circle(float _x, float _y, float _rad);
	~Circle(); //����������
	//�������, �������
	float getrad();
	void setrad(float _rad);
	// ����������� ������� �����������
	virtual void moveTo(float _x, float _y) override;	
	// ������������� ���������
	friend bool operator == (const Circle& circle1, const Circle& circle2);
	friend bool operator != (const Circle& circle1, const Circle& circle2);
	friend ostream& operator<< (ostream& out, const Circle& dot);
	friend istream& operator>> (istream& in, Circle& dot);
};