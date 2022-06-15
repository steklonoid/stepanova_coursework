#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include "Dot.h"
#include "Сircle.h"
#include "Sector.h"
using namespace std;

template <class T> //обЪявляем шаблонный класс итератор
class FigIterator;

template <class T> //шаблонный класс контейнер
class Fig
{
private:
	T* arr;	//свойство класса - динамический массив, содержащий элементы контейнера
	int size;//свойство класса - размер массива
	bool allowCopyEl;//свойства класса - разрешено ли хранить одинаковые элементы
public:
	// конструктор по умолчанию: инициализирует пустой массив, размер устанавливает в 0
	Fig() :arr(new T[0]), size(0), allowCopyEl(false) {}
	// конструктор копирования
	Fig(const Fig& fig)       
	{
		delete[] arr; //удаляем текущий массив
		size = fig.size; //копируем размер
		allowCopyEl = fig.allowCopyEl;
		arr = new T[size]; //создаем массив с размером size
		for (int i = 0; i < size; i++) //поэлементвно копируем элементы масссива
		{
			arr[i] = fig.arr[i];
		}
	}
	// деструктор
	~Fig()
	{
		delete[] arr; //удаляем массив - освобождаем память, занятую динамическим массивом
	}
	//геттеры, сеттеры
	bool get_allowCopyEl() { return allowCopyEl; }
	void set_allowCopyEl(bool _value) { allowCopyEl = _value; }
	// метод возращает объект класса итератора, указывающий на начало массива
	FigIterator <T> begin()
	{				
		return FigIterator<T>(arr);
	}
	// метод возращает объект класса итератора, указывающий на конец массива
	FigIterator <T> end()
	{
		return FigIterator<T>(arr + size);
	}
	Fig& operator =(const Fig& fig)
	{
		delete[] arr; //удаляем текущий массив
		size = fig.size; //копируем размер
		allowCopyEl = fig.allowCopyEl;
		arr = new T[size]; //создаем массив с размером size
		for (int i = 0; i < size; i++) //поэлементвно копируем элементы масссива
		{
			arr[i] = fig.arr[i];
		}
		return *this;
	}
	//перегруженные операторы возращают элемент массива с индексом index
	T& operator [](int index)
	{
		return	arr[index];
	}
	const T& operator [](int index) const
	{
		return arr[index];
	}
	//метод возвращает размер массива
	int sizearr() const
	{
		return size;
	}
	//метод проверяет есть ли элемент в массиве
	bool consist(T el)
	{
		bool fl = false;
		int i;
		for (i = 0; i < size; i++)	// в цикле копируем все элементы текущего массива во временный
		{
			if (arr[i] == el)
			{
				fl = true;
				break;
			}
		}
		return fl;
	}
	//метод добавляем элемент в конец массива
	void addEl(T el)
	{					
		//if (!consist(_el) || allowCopyEl)	//добавляем если нету еще такого элемента или копии разрешены
		//{
			int i = 0;
			T* newarr = new T[size + 1];//создаем временный динамический массив размером на один больше текущего массива контейнера
			for (i = 0; i < size; i++)	// в цикле копируем все элементы текущего массива во временный
			{
				newarr[i] = arr[i];
			}
			newarr[i] = el;	//добавляем новый элемент
			delete[] arr;	//удаляем текущий массив
			arr = newarr;	//делаем временный массив текущим
			size++;			//увеличиваем переменную размера массива на один
		//}
	}
	//метод удаляет элемент из массива по индексу
	void removeByIndex(int index)
	{	
		if (index < size && size > 0) //проверка корректности индекса
		{
			int j = 0;
			T* newarr = new T[size - 1];	//создаем временный динамический массив размером на один меньше текущего массива контейнера
			for (int i = 0; i < size; i++)	// в цикле копируем все элементы текущего массива во временный...
			{	
				if (i != index)		//...кроме элемента с индексом
				{
					newarr[j] = arr[i];
					j++;
				}				
			}			
			delete[] arr;	//удаляем текущий массив
			arr = newarr;	//делаем временный массив текущим
			size--;			//уменьшаем переменную размера массива на один
		}
	}
	//метод удаляет из массива все заданные элементы
	void removeEl(T el)
	{
		int i, j;
		// подсчитываем количество элементов, поллежащих удалению
		int counter = 0;
		for (i = 0; i < size; i++)
		{
			if (arr[i] == el)
			{
				counter++;
			}
		}
		if (counter > 0)
		{
			T* newarr = new T[size - counter];	//создаем временный динамический массив размером на один меньше текущего массива контейнера
			j = 0;
			for (int i = 0; i < size; i++)	// в цикле копируем все элементы текущего массива во временный...
			{
				if (arr[i] != el)		//...кроме элемента с индексом
				{
					newarr[j] = arr[i];
					j++;
				}
			}
			delete[] arr;	//удаляем текущий массив
			arr = newarr;	//делаем временный массив текущим
			size = size - counter;			//уменьшаем переменную размера массива на один
		}
	}	
	//метод удаляем все элементы массива
	void removeAll()
	{
		delete[] arr;	//удаляем текущий массив
		arr = new T[0];	//создаем новый текущий массив размером 0
		size = 0;		//задаем переменную размера массива равной 0
	}
};
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
