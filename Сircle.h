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
	// виртуальна€ функци€ перемещени€
	virtual void moveTo(float _x, float _y) override
	{
		x = _x;
		y = _y;
	}
	// перегруженные операторы
	friend bool operator == (const Circle& circle1, const Circle& circle2);
	friend bool operator != (const Circle& circle1, const Circle& circle2);
	friend ostream& operator<< (ostream& out, const Circle& dot);
	friend istream& operator>> (istream& in, Circle& dot);
};
//перегруженные операторы сравнени€
bool operator == (const Circle& circle1, const Circle& circle2)
{
	return circle1.x == circle2.x && circle1.y == circle2.y && circle1.rad == circle2.rad;
}
bool operator != (const Circle& circle1, const Circle& circle2)
{
	return !(circle1 == circle2);
}
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
