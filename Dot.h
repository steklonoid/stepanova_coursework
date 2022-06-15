#pragma once
#include <iostream>
#include <string>
using namespace std;
class Dot
{
protected:	
	float x, y;

public:
	Dot()	//конструктор по умолчанию
	{
		x = y = 0;
	}
	Dot(float _x, float _y) // конструктор с параметрами
	{
		x = _x;
		y = _y;
	}
	Dot(const Dot& from_dot)	//конструктор копирования
	{
		x = from_dot.x;
		y = from_dot.y;
	}	
	~Dot(){}	//деструктор
	// геттеры, сеттеры
	float getx() { return x; }
	void setx(float _x) { x = _x; }
	float gety() { return y; }
	void sety(float _y) { y = _y; }
	// виртуальная функция перемещения
	virtual void moveTo(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	//перегруженные операторы
	friend Dot operator + (const Dot& dot1, const Dot& dot2);
	friend Dot operator * (const Dot& dot, float koef);
	friend Dot operator - (const Dot& dot1, const Dot& dot2);
	friend Dot operator / (const Dot& dot, float koef);
	friend bool operator == (const Dot& dot1, const Dot& dot2);
	friend bool operator != (const Dot& dot1, const Dot& dot2);
	friend ostream& operator<< (ostream& out, const Dot& dot);
	friend istream& operator>> (istream& in, Dot& dot);
};
// перегруженные оператор вывода объекта
ostream& operator<< (ostream& out, const Dot& dot)
{	
	out << "x: " << dot.x<< " y: " << dot.y << "\n";
	return out;
}
//перегруженный оператор ввода объекта
istream& operator>> (istream& in, Dot& dot)
{	
	cout << "Enter x: ";
	cin >> dot.x;	
	cout << "Enter y: ";	
	cin >> dot.y;
	return in;
}
//перегруженный оператор сложения двух точек
Dot operator + (const Dot& dot1, const Dot& dot2)
{
	Dot dot3;
	dot3.x = dot1.x + dot2.x;
	dot3.y = dot1.y + dot2.y;
	return dot3;
}
//перегруженный оператор умножения на коэффициент
Dot operator * (const Dot& dot, float koef)
{
	Dot dot1;
	dot1.x = dot.x * koef;
	dot1.y = dot.y * koef;
	return dot1;
}
//перегруженный оператор деления на коэффициент
Dot operator / (const Dot& dot, float koef)
{
	Dot dot1;
	if (koef != 0)
	{
		dot1.x = dot.x / koef;
		dot1.x = dot.x / koef;
	}
	return dot1;
}
//перегруженный оператор вычитания двух точек
Dot operator - (const Dot& dot1, const Dot& dot2)
{
	Dot dot3;
	dot3.x = dot1.x - dot2.x;
	dot3.y = dot1.y - dot2.y;
	return dot3;
}
//перегруженные операторы сравнения
bool operator == (const Dot& dot1, const Dot& dot2)
{	
	return dot1.x == dot2.x && dot1.y == dot2.y;
}
bool operator != (const Dot& dot1, const Dot& dot2)
{
	return !(dot1 == dot2);
}