#include "Сircle.h"
Circle::Circle() : Dot(), rad(0)
{
}
// конструктор с параметрами
Circle::Circle(float _x, float _y, float _rad) : Dot(_x, _y), rad(_rad)
{
}
Circle::~Circle() {}//деструктор
//геттеры, сеттеры
float Circle::getrad() { return rad; }
void Circle::setrad(float _rad) { rad = _rad; }
// виртуальная функция перемещения
void Circle::moveTo(float _x, float _y)
{
	x = _x;
	y = _y;
}
//перегруженные операторы сравнения
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
	cin >> circle.x;
	cout << "Enter y: ";
	cin >> circle.y;
	cout << "Enter radius: ";
	cin >> circle.rad;
	return in;
}