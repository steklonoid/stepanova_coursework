#pragma once
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