#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <conio.h>
#include "Dot.h"
#include "�ircle.h"
#include "Sector.h"
#include "Figura.h"
using namespace std;

template <typename T1, typename T2, typename T3>
void menu2(T1& cont, T2& el, T3& iter, string name) //��������� ������� �������
{   
    int j, index;
    float x, y;
    Dot* p; // ��������� ��������� �� ������� ����� ��� ���������� �������� ���������� ����������� ������� moveTo

    do {
        system("cls");
        cout << "----------------------------------------\n";   // ����� ����
        cout << "1.Add " << name << "\n2.Show all " << name << "s\n3.Move " << name << " \n4.Delete " << name << " by index\n5.Delete all " << name << "s\n6.Previous menu\n";
        cout << "----------------------------------------\n";        
        cin >> j;           //������ ������ ������ ����
        switch (j)
        {
        case 1:
            cin >> el;      // ������ ���������� �� ��������, ��������� ������������� ������� ����� >>
            cont.addEl(el); //��������� ������ ������ � ���������
            break;
        case 2:
            if (cont.sizearr() == 0)    // ��������� ������ ����������, ���� = 0, ������� ��������� �� ���������� ���������
            {
                cout << " no any " << name << "s";
            }
            else
            {
                iter = cont.begin(); //������ �������� �� ������ ����������                
                int counter = 0;     //������������� ���������� ��� �������� ����������
                while (iter != cont.end()) //���� �� ������ �� ���������� �������� ����������
                {
                    counter++;                        //������� ������� ����������
                    cout << counter << ". " << *iter; //������������� * �� ������ ��������� ���������� ������ �� ������� ������� ����������, 
                                                      //����� �������� �������������� ����� ������������� �������� ������ <<
                    iter++;                           //������������� ++ �������� ��������  
                }
            }
            getch();    
            break;
        case 3:
            cout << "Enter index less then " << cont.sizearr()+1 << "\n"; // ������ ������� �������� � ����������
            cin >> index;
            index--;
            if (index < cont.sizearr() && index >=0)    //�������� ������������ ����� ������� 
            {           
                cout << cont[index] << "\n";    // ����� ���������� �� �������� ����� ������������� �������� �������� <<, 
                                                // ����� ������������ ������������� �������� [ ] ����������
                cout << "Enter new x: ";        // ������ ����� x
                cin >> x;
                cout << "Enter new y: ";        // ������ ����� y
                cin >> y;
                p = &cont[index];               // ����������� ��������� p ����� ������� �������� ����������
                p->moveTo(x, y);                // ����� ����������� �������
                cout << "Checking:\n";
                cout << cont[index] << "\n";    //����������� �����
                getch();
            }
            break;
        case 4:            
            cout << "Enter index less then " << cont.sizearr() << "\n"; // ������ ������� �������� � ����������
            cin >> index;
            if (index < cont.sizearr() && index >= 0)   //�������� ������������ ����� ������� 
            {
                cont.removeByIndex(index); //����� ������ ����������
            }
            break;
        case 5:
            cont.removeAll(); //����� ������ ����������
            break;
        case 6:
            break;
        default:
            break;
        }
    } while (j != 6);    
}

template <typename T1, typename T2>
void loaddb(T1& cont, T2& el, string filename) //��������� ������� �������� ������ �� �����
{
    int n;
    fstream db;
    db.open(filename, ios::in | ios::binary);   //��������� �������� ���� �� ������
    if (db)
    {
        db.read((char*)&n, sizeof(int));        //������ �� ����� � ���������� n ������ ������ - ���������� ���������� ��������
        for (int i = 0; i < n; i++)             // � ����� n ��� 
        {
            db.read((char*)&el, sizeof(el));    //������ �� ����� � ���������� el ���������� �������
            cont.addEl(el);                     //��������� � ���������
        }
    }
    db.close();                                 //��������� ����
}

template <typename T1, typename T2, typename T3>
void savedb(T1& cont, T2& el, T3& iter, string filename) //��������� ������� ���������� ������ � ����
{
    fstream db;
    db.open(filename, ios::out | ios::binary);  //��������� �������� ���� �� ������
    int n = cont.sizearr();                     // �������� ������ ����������
    db.write((char*)&n, sizeof(int));           //���������� � ���� ������ ������� ������ ����������
    iter = cont.begin();                        //������ �������� �� ������ ����������
    while (iter != cont.end())                  //���� �������� �� ������ ����� ����������
    {
        el = *iter;                             //�������� ������� ���������� ����� ������������� *
        db.write((char*)&el, sizeof(el));       //������ �������� � ����
        iter++;                                 //������������� ++ �������� ��������
    }
    db.close();
}
//������� ���������� ������������ �� ��� ����������
bool intersect(Circle c1, Circle c2)
{
    float dist = sqrt(pow((c2.getx() - c1.getx()), 2) + pow((c2.gety() - c1.gety()), 2));
    float sumrad = c1.getrad() + c2.getrad();
    return dist <= sumrad;
}

void find_clusters(Fig<Circle>& circles)
{
    // ������������� ����������
    vector<vector<Circle>> clusters;
    Fig<Circle> free_circles;
    Fig<Circle> first_wave;
    Fig<Circle> second_wave; 

    int i, j;
    free_circles = circles; //�����, ������� ��� �� � ��������� - ���������� ���
    while (true)
    {
        if (free_circles.sizearr() != 0)    // ���� �������� ��� ����� �� � ���������
        {
            vector<Circle> cluster;             // �������������� ����� �������
            cluster.push_back(free_circles[0]); // ��������� � ���� ������ ��������� ����
            first_wave.removeAll();             //  ������� ��������������� ������ 1
            first_wave.addEl(free_circles[0]);  // ��������� � ���� ���� �� ��������� ����            
            free_circles.removeByIndex(0);      // �.�. ���� �������� � �������, ��������� ��� �� ������� ��������� ������
            while (true)
            {
                FigIterator<Circle> iter1 = first_wave.begin(); //������������� ��������� ��� ������� �� ������� 1
                while (iter1 != first_wave.end())
                {
                    Circle c1 = *iter1;                         // ������� ���� �� ������� 1
                    FigIterator<Circle> iter2 = circles.begin();// ������������� ��������� ��� ������� �� ���� ������
                    while (iter2 != circles.end())
                    {
                        Circle c2 = *iter2;                     //������� ���� �� ������� ���� ������
                        if (free_circles.consist(c2))           // ���� �2 �������� (��� �� � ��������)...
                        {
                            if (intersect(c1, c2))              //...��������� ��� ����������� � ������ �1 �� ������� 1
                            {
                                second_wave.addEl(c2);          //���� ������������, ��������� ��� � ������ 2                                
                            }
                        }
                        iter2++;
                    }
                    iter1++;
                }
                if (second_wave.sizearr() == 0)                 // ���� �� ����� ������ � �������� ������������ ����� �� ������� 1
                {
                    break;                                      // ��������� - ������� ��������
                }
                else
                {
                    first_wave = second_wave;                   // ������ ������ ���������� ������ - � ����. ������� ����� ����� ������
                                                                // ����������� ��� � ������� �� ����� �������
                    FigIterator<Circle> iter = second_wave.begin(); // � ��������� ��� ����� �� ������� ������� � �������
                    while (iter != second_wave.end())
                    {
                        Circle c = *iter;
                        cluster.push_back(c);                   //��������� � ������� �
                        free_circles.removeEl(c);               //��������� �� ������� ��������� ������
                        iter++;
                    }
                    second_wave.removeAll();                    //��� ���� ������� ����� ������� ������ 2
                }
            }
            clusters.push_back(cluster);                        // ��������� ������� � ������ ���������
        }
        else
        {
            break;                                              // ���� ������ ����� ��������� �� �������� - ��� ����� ��������� - �������
        }
    }
    // ����� ���������� � ���������
    for (i = 0; i < clusters.size(); i++)
    {
        cout << "Cluster " << i << ".\n";
        for (j = 0; j < clusters[i].size(); j++)
        {
            cout << "   " << clusters[i][j] << "";
        }
    }
}

int main()
{    
    // ���������� ����������
    Dot dot;                                            
    Circle circle;    
    Sector sector;

    Fig<Dot> dots;
    Fig<Circle> circles;
    Fig<Sector> sectors;

    FigIterator<Dot> dotiter = dots.begin();
    FigIterator<Circle> circleiter = circles.begin();
    FigIterator<Sector> sectoriter = sectors.begin();

    string dotsdb = "dots.data";
    string circlesdb = "circles.data";
    string sectorsdb = "sectors.data";

    fstream db;           

       

    // �������� �������� ������� ������ ������ �� �����, ��������������� ��� 3 �����������
    loaddb<Fig<Dot>, Dot>(dots, dot, dotsdb);               
    loaddb<Fig<Circle>, Circle>(circles, circle, circlesdb);
    loaddb<Fig<Sector>, Sector>(sectors, sector, sectorsdb);

    int i, j, n;    
    do {
        // ����� ���� �������� ������
        system("cls");              //������� �����
        cout << "----------------------------------------\n";
        cout << "1. Dots\n2. Circles\n3. Sectors\n4. Find circle cluster\n5. Summury info\n6. Save DB\n7. Exit\n"; 
        cout << "----------------------------------------\n";
        cin >> i;   //������ ������ ������ ����
        switch (i)
        {
        case 1:
            menu2<Fig<Dot>, Dot, FigIterator<Dot>>(dots, dot, dotiter, "dot");                      //����� ������� ������ � �������� ������� ��� �����
            break;
        case 2:
            menu2<Fig<Circle>, Circle, FigIterator<Circle>>(circles, circle, circleiter, "circle"); //����� ������� ������ � �������� ������� ��� ������
            break;
        case 3:
            menu2<Fig<Sector>, Sector, FigIterator<Sector>>(sectors, sector, sectoriter, "sector"); //����� ������� ������ � �������� ������� ��� ��������
            break;
        case 4:
            find_clusters(circles);             // ����� ������� ������ �������� �������������� �����������            
            getch();
            break;
        case 5:
            cout << dots.sizearr() << " dots\n";        //������� ������ ���������� ��� �����
            cout << circles.sizearr() << " circles\n";  //������� ������ ���������� ��� ������
            cout << sectors.sizearr() << " sectors\n";  //������� ������ ���������� ��� ��������
            getch();
            break;
        case 6:
            // �������� �������� ������� ������ ������ � ����, ��������������� ��� 3 �����������
            savedb<Fig<Dot>, Dot, FigIterator<Dot>>(dots, dot, dotiter, dotsdb);                     
            savedb<Fig<Circle>, Circle, FigIterator<Circle>>(circles, circle, circleiter, circlesdb);
            savedb<Fig<Sector>, Sector, FigIterator<Sector>>(sectors, sector, sectoriter, sectorsdb);
            break;
        case 7:                                    
            break;        
        default:
            break;
        }
    } while (i != 7);
    
    return 0;
}