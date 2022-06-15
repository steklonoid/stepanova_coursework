#pragma once
#include <iostream>
#include <string>
#include "Сircle.h"
using namespace std;
//производный от Circle класс
class Sector: public Circle
{
protected:
	float a, b;

public:
	//конструктор по умолчанию
	Sector():Circle(), a(0), b(0)
	{		
	}
	//конструктор с параметрами
	Sector(float _x, float _y, float _rad, float _a, float _b): Circle(_x, _y, _rad), a(_a), b(_b)
	{
	}
	~Sector(){}//деструктор
	//гетеры, сеттеры
	float geta() { return a; }
	void seta(float _a) { a = _a; }
	float getb() { return b; }
	void setb(float _b) { b = _b; }
	//виртуальная функция перемещения
	virtual void moveTo(float _x, float _y) override
	{
		x = _x;
		y = _y;
	}
	//перегруженные операторы
	friend bool operator == (const Sector& sector1, const Sector& sector2);
	friend bool operator != (const Sector& sector1, const Sector& sector2);
	friend ostream& operator<< (ostream& out, const Sector& sector);
	friend istream& operator>> (istream& in, Sector& sector);
};
bool operator == (const Sector& sector1, const Sector& sector2)
{
	return sector1.x == sector2.x && sector1.y == sector2.y && sector1.rad == sector2.rad && sector1.a == sector2.a && sector1.b == sector2.b;
}
bool operator != (const Sector& sector1, const Sector& sector2)
{
	return !(sector1 == sector2);
}
//перегруженный оператор вывода
ostream& operator<< (ostream& out, const Sector& sector)
{	
	out << "x: " << sector.x << " y: " << sector.y << " radius: " << sector.rad << " a: " << sector.a << " b: " << sector.b << "\n";
	return out;
}
//перегруженный оператор ввода
istream& operator>> (istream& in, Sector& sector)
{	
	cout << "Enter x: ";
	cin >> sector.x;
	cout << "Enter y: ";
	cin >> sector.y;
	cout << "Enter radius: ";
	cin >> sector.rad;
	cout << "Enter alpha: ";
	cin >> sector.a;
	cout << "Enter beta: ";
	cin >> sector.b;
	return in;
}

