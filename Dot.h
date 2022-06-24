#pragma once
#include <iostream>
#include <string>
using namespace std;
class Dot
{
protected:	
	float x, y;

public:
	Dot(); 	//конструктор по умолчанию	
	Dot(float _x, float _y); // конструктор с параметрами
	Dot(const Dot& from_dot);	//конструктор копирования
	~Dot();	//деструктор
	// геттеры, сеттеры
	float getx();
	void setx(float _x);
	float gety();
	void sety(float _y);
	// виртуальная функция перемещения
	virtual void moveTo(float _x, float _y);
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