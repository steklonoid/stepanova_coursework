#pragma once
#include <iostream>
#include <string>
#include "Dot.h"
using namespace std;
// производный от Dot класс
class Circle: public Dot
{
protected:
	float rad;

public:
	// конструктор по умолчанию
	Circle();
	// конструктор с параметрами
	Circle(float _x, float _y, float _rad);
	~Circle(); //деструктор
	//геттеры, сеттеры
	float getrad();
	void setrad(float _rad);
	// виртуальная функция перемещения
	virtual void moveTo(float _x, float _y) override;	
	// перегруженные операторы
	friend bool operator == (const Circle& circle1, const Circle& circle2);
	friend bool operator != (const Circle& circle1, const Circle& circle2);
	friend ostream& operator<< (ostream& out, const Circle& dot);
	friend istream& operator>> (istream& in, Circle& dot);
};