#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include "Dot.h"
#include "Сircle.h"
#include "Sector.h"
using namespace std;

template <class T> //обЪявляем шаблонный класс итератор?
class FigIterator;

template <class T> //шаблонный класс
class Fig
{
private:
	T* arr;
	int size;
public:
	Fig() :arr(new T[0]), size(0) {} //конструктор создает пустой массив
	Fig(const Fig& fig)              //конструктор с параметрами?
	{
		delete arr;       
		size = fig.size; 
		arr = new T[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = fig.arr[i];
		}
	}
	~Fig()
	{
		delete[] arr;
	}

	FigIterator <T> begin()
	{
		return FigIterator<T>(arr);
	}
	FigIterator <T> end()
	{
		return FigIterator<T>(arr + size);
	}
	T& operator [](int index)
	{
		return arr[index];
	}
	const T& operator [](int index) const
	{
		return arr[index];
	}
	int sizearr() const
	{
		return size;
	}
	void addEl(T el)
	{				
		int i = 0;
		T* newarr = new T[size + 1];
		for (i = 0; i < size; i++)
		{
			newarr[i] = arr[i];
		}
		newarr[i] = el;
		delete[] arr;
		arr = newarr;
		size++;
	}
	void removeEl(int index)
	{	
		if (index < size && size > 0)
		{
			int j = 0;
			T* newarr = new T[size - 1];
			for (int i = 0; i < size; i++)
			{	
				if (i != index)
				{
					newarr[j] = arr[i];
					j++;
				}				
			}			
			delete[] arr;
			arr = newarr;
			size--;
		}
	}
	void removeAll()
	{
		delete[] arr;
		arr = new T[0];
		size = 0;
	}
};

template<class T>
class FigIterator
{
private:
	T* current;
public:
	FigIterator(T* curr) :current(curr)
	{
	}
	FigIterator& operator =(const FigIterator& other)
	{
		if (this != &other)
		{
			current = other.current;
		}
		return *this;
	}
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
	T& operator *()
	{
		return *current;
	}
	T* operator ->()
	{
		return current;
	}
	bool operator ==(const FigIterator& other)
	{
		return current == other.current;
	}
	bool operator !=(const FigIterator& other)
	{
		return !(*this == other);
	}
};
