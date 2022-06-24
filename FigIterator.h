#pragma once
//шаблонный класс итератор
template<class T>
class FigIterator
{
private:
	T* current; //свойство current хранит указатель на элемент контейнера
public:
	//конструктор с параметром
	//при создании объекта класса итератора, мы должны передать в него указатель на элемент контейнера
	FigIterator(T* curr) :current(curr)
	{
	}
	//перегруженный оператор присваивания
	FigIterator& operator =(const FigIterator& other)
	{
		if (this != &other)
		{
			current = other.current; // копируем свойство current
		}
		return *this;
	}
	//перегруженные операторы сдвига итератора, увеличивают адрес указателя current на размер обекта T
	FigIterator& operator ++()
	{
		++current;
		return *this;
	}
	FigIterator operator ++(int i)
	{
		FigIterator tmp(current);
		++current;
		return tmp;
	}
	// перегруженный оператор возвращает указатель current на объект T
	T& operator *()
	{
		return *current;
	}
	T& operator ->()
	{
		return current;
	}
	//перегруженные операторы сравненния
	bool operator ==(const FigIterator& other)
	{
		return current == other.current;
	}
	bool operator !=(const FigIterator& other)
	{
		return !(*this == other);
	}
};