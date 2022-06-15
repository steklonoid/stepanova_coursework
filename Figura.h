#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include "Dot.h"
#include "�ircle.h"
#include "Sector.h"
using namespace std;

template <class T> //��������� ��������� ����� ��������
class FigIterator;

template <class T> //��������� ����� ���������
class Fig
{
private:
	T* arr;	//�������� ������ - ������������ ������, ���������� �������� ����������
	int size;//�������� ������ - ������ �������
	bool allowCopyEl;//�������� ������ - ��������� �� ������� ���������� ��������
public:
	// ����������� �� ���������: �������������� ������ ������, ������ ������������� � 0
	Fig() :arr(new T[0]), size(0), allowCopyEl(false) {}
	// ����������� �����������
	Fig(const Fig& fig)       
	{
		delete[] arr; //������� ������� ������
		size = fig.size; //�������� ������
		allowCopyEl = fig.allowCopyEl;
		arr = new T[size]; //������� ������ � �������� size
		for (int i = 0; i < size; i++) //������������ �������� �������� ��������
		{
			arr[i] = fig.arr[i];
		}
	}
	// ����������
	~Fig()
	{
		delete[] arr; //������� ������ - ����������� ������, ������� ������������ ��������
	}
	//�������, �������
	bool get_allowCopyEl() { return allowCopyEl; }
	void set_allowCopyEl(bool _value) { allowCopyEl = _value; }
	// ����� ��������� ������ ������ ���������, ����������� �� ������ �������
	FigIterator <T> begin()
	{				
		return FigIterator<T>(arr);
	}
	// ����� ��������� ������ ������ ���������, ����������� �� ����� �������
	FigIterator <T> end()
	{
		return FigIterator<T>(arr + size);
	}
	Fig& operator =(const Fig& fig)
	{
		delete[] arr; //������� ������� ������
		size = fig.size; //�������� ������
		allowCopyEl = fig.allowCopyEl;
		arr = new T[size]; //������� ������ � �������� size
		for (int i = 0; i < size; i++) //������������ �������� �������� ��������
		{
			arr[i] = fig.arr[i];
		}
		return *this;
	}
	//������������� ��������� ��������� ������� ������� � �������� index
	T& operator [](int index)
	{
		return	arr[index];
	}
	const T& operator [](int index) const
	{
		return arr[index];
	}
	//����� ���������� ������ �������
	int sizearr() const
	{
		return size;
	}
	//����� ��������� ���� �� ������� � �������
	bool consist(T el)
	{
		bool fl = false;
		int i;
		for (i = 0; i < size; i++)	// � ����� �������� ��� �������� �������� ������� �� ���������
		{
			if (arr[i] == el)
			{
				fl = true;
				break;
			}
		}
		return fl;
	}
	//����� ��������� ������� � ����� �������
	void addEl(T el)
	{					
		//if (!consist(_el) || allowCopyEl)	//��������� ���� ���� ��� ������ �������� ��� ����� ���������
		//{
			int i = 0;
			T* newarr = new T[size + 1];//������� ��������� ������������ ������ �������� �� ���� ������ �������� ������� ����������
			for (i = 0; i < size; i++)	// � ����� �������� ��� �������� �������� ������� �� ���������
			{
				newarr[i] = arr[i];
			}
			newarr[i] = el;	//��������� ����� �������
			delete[] arr;	//������� ������� ������
			arr = newarr;	//������ ��������� ������ �������
			size++;			//����������� ���������� ������� ������� �� ����
		//}
	}
	//����� ������� ������� �� ������� �� �������
	void removeByIndex(int index)
	{	
		if (index < size && size > 0) //�������� ������������ �������
		{
			int j = 0;
			T* newarr = new T[size - 1];	//������� ��������� ������������ ������ �������� �� ���� ������ �������� ������� ����������
			for (int i = 0; i < size; i++)	// � ����� �������� ��� �������� �������� ������� �� ���������...
			{	
				if (i != index)		//...����� �������� � ��������
				{
					newarr[j] = arr[i];
					j++;
				}				
			}			
			delete[] arr;	//������� ������� ������
			arr = newarr;	//������ ��������� ������ �������
			size--;			//��������� ���������� ������� ������� �� ����
		}
	}
	//����� ������� �� ������� ��� �������� ��������
	void removeEl(T el)
	{
		int i, j;
		// ������������ ���������� ���������, ���������� ��������
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
			T* newarr = new T[size - counter];	//������� ��������� ������������ ������ �������� �� ���� ������ �������� ������� ����������
			j = 0;
			for (int i = 0; i < size; i++)	// � ����� �������� ��� �������� �������� ������� �� ���������...
			{
				if (arr[i] != el)		//...����� �������� � ��������
				{
					newarr[j] = arr[i];
					j++;
				}
			}
			delete[] arr;	//������� ������� ������
			arr = newarr;	//������ ��������� ������ �������
			size = size - counter;			//��������� ���������� ������� ������� �� ����
		}
	}	
	//����� ������� ��� �������� �������
	void removeAll()
	{
		delete[] arr;	//������� ������� ������
		arr = new T[0];	//������� ����� ������� ������ �������� 0
		size = 0;		//������ ���������� ������� ������� ������ 0
	}
};
//��������� ����� ��������
template<class T>
class FigIterator
{
private:
	T* current; //�������� current ������ ��������� �� ������� ����������
public:
	//����������� � ����������
	//��� �������� ������� ������ ���������, �� ������ �������� � ���� ��������� �� ������� ����������
	FigIterator(T* curr) :current(curr)
	{		
	}
	//������������� �������� ������������
	FigIterator& operator =(const FigIterator& other)
	{
		if (this != &other)
		{
			current = other.current; // �������� �������� current
		}
		return *this;
	}
	//������������� ��������� ������ ���������, ����������� ����� ��������� current �� ������ ������ T
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
	// ������������� �������� ���������� ��������� current �� ������ T
	T& operator *()
	{
		return *current;
	}
	T& operator ->()
	{
		return current;
	}
	//������������� ��������� ����������
	bool operator ==(const FigIterator& other)
	{
		return current == other.current;
	}
	bool operator !=(const FigIterator& other)
	{
		return !(*this == other);
	}
};
