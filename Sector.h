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
	Sector();
	//конструктор с параметрами
	Sector(float _x, float _y, float _rad, float _a, float _b);
	~Sector();//деструктор
	//гетеры, сеттеры
	float geta();
	void seta(float _a);
	float getb();
	void setb(float _b);
	//виртуальная функция перемещения
	virtual void moveTo(float _x, float _y) override;
	//перегруженные операторы
	friend bool operator == (const Sector& sector1, const Sector& sector2);
	friend bool operator != (const Sector& sector1, const Sector& sector2);
	friend ostream& operator<< (ostream& out, const Sector& sector);
	friend istream& operator>> (istream& in, Sector& sector);
};