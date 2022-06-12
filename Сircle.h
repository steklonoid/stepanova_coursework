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
	Circle(): Dot(), rad(0)
	{		
	}
	// конструктор с параметрами
	Circle(float _x, float _y, float _rad): Dot(_x, _y), rad(_rad)
	{
	}
	~Circle() {}//деструктор
	//геттеры, сеттеры
	float getrad() { return rad; }
	void setrad(float _rad) { rad = _rad; }
	// виртуальная функция перемещения
	virtual void moveTo(float _x, float _y) override
	{
		x = _x;
		y = _y;
	}
	// перегруженные операторы
	friend ostream& operator<< (ostream& out, const Circle& dot);
	friend istream& operator>> (istream& in, Circle& dot);
};
//перегруженны оператор вывода
ostream& operator<< (ostream& out, const Circle& circle)
{	
	out << "x: " << circle.x << " y: " << circle.y << " radius: " << circle.rad << "\n";
	return out;
}
//перегруженный оператор ввода
istream& operator>> (istream& in, Circle& circle)
{	
	cout << "Enter x: ";
	cin >>	circle.x;
	cout << "Enter y: ";
	cin >> circle.y;
	cout << "Enter radius: ";
	cin >> circle.rad;
	return in;
}
