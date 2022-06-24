#include "Dot.h"
Dot::Dot()	//конструктор по умолчанию
{
	x = y = 0;
}
Dot::Dot(float _x, float _y) // конструктор с параметрами
{
	x = _x;
	y = _y;
}
Dot::Dot(const Dot& from_dot)	//конструктор копирования
{
	x = from_dot.x;
	y = from_dot.y;
}
Dot::~Dot() {}	//деструктор
// геттеры, сеттеры
float Dot::getx() { return x; }
void Dot::setx(float _x) { x = _x; }
float Dot::gety() { return y; }
void Dot::sety(float _y) { y = _y; }
// виртуальная функция перемещения
void Dot::moveTo(float _x, float _y)
{
	x = _x;
	y = _y;
}
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
		dot1.y = dot.y / koef;
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