#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <Windows.h>
#include <conio.h>
#include "Dot.h"
#include "�ircle.h"
#include "Sector.h"
#include "Figura.h"
using namespace std;

// ���������� ���������� ������ ���� ���������� ���������
int language;

//������� �����������
string menu_locale(int menu_n, int loc)
{
    string res;
    switch (menu_n)
    {
    case 1:
        switch (loc)
        {
        case 1:
            res = "1. Dots\n2. Circles\n3. Sectors\n4. Find circle cluster\n5. Summury info\n6. Save DB\n7. Autotesting\n8. Exit\n";
            break;
        case 2:
            res = "1. �����\n2. �����\n3. �������\n4. ����� ������� ������\n5. ����� ����������\n6. ��������� ����\n7. ����������������\n8. �����\n";
            break;
        case 3:
            res = "1. �����\n2. ����\n3. �������\n4. ������ ������� ��\n5. �������� ����������\n6. �������� ����\n7. ��������������\n8. �����\n";
            break;
        }
        break;
    case 2:
        switch (loc)
        {
        case 1:
            res = "1.Add\n2.Show all\n3.Move\n4.Delete by index\n5.Delete all\n6.Previous menu\n";
            break;
        case 2:
            res = "1.��������\n2.�������� ���\n3.�����������\n4.������� �� �������\n5.������� ���\n6.���������� ����\n";
            break;
        case 3:
            res = "1.������\n2.�������� ��\n3.����������\n4.�������� �� ��������\n5.�������� ��\n6.�������� ����\n";
            break;
        }
        break;
    case 3:
        switch (loc)
        {
        case 1:
            res = "no objects";
            break;
        case 2:
            res = "���� ��������";
            break;
        case 3:
            res = "������� ��'����";
            break;
        }
    }
    return res;
}

template <typename T1, typename T2, typename T3>
void menu2(T1& cont, T2& el, T3& iter) //��������� ������� �������
{   
    int j, index;
    float x, y;
    Dot* p; // ��������� ��������� �� ������� ����� ��� ���������� �������� ���������� ����������� ������� moveTo

    do {
        system("cls");
        cout << "----------------------------------------\n";   // ����� ����
        cout << menu_locale(2, language);
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
                cout << menu_locale(3, language);
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
                p->moveTo(x, y);                // ����� ����������� �������, ����� �������� �������� ����������
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

//********************************************************************************
void Autotesting()
{
    cout << "������������ ������ Dot\n";
    cout << "����������� �� ��������� <Dot d1>\n";
    Dot d1;
    cout << "������� <d1.getx(), d1.gety()>\n";
    cout << d1.getx() << endl;
    cout << d1.gety() << endl;
    cout << "������� <d3.setx(8), d3.sety(9)>\n";
    d1.setx(8);
    d1.sety(9);
    cout << d1.getx() << endl;
    cout << d1.gety() << endl;
    cout << "������������� �������� ������ <<\n";
    cout << d1 << "\n";
    cout << "������������� �������� ����� >>\n";
    cin >> d1;
    cout << d1 << "\n";
    getch();
    cout << "����������� c ����������� <Dot d2(3, 4)>\n";
    Dot d2(3, 4);
    cout << d2 << "\n";
    cout << "����������� ����������� <Dot d3 = d2;>\n";
    Dot d3 = d2;
    cout << d3 << "\n";            
    cout << "����������� <moveTo(11, 12)>\n";
    Dot* p;
    p = &d3;               
    p->moveTo(11, 12);
    cout << d3 << "\n";
    cout << "������������� �������� + \n<Dot(7, 3) + Dot(3, 8)>\n";
    cout << Dot(7, 3) + Dot(3, 8) << "\n";
    cout << "������������� �������� - \n<Dot(12, 12) - Dot(6, 2)>\n";
    cout << Dot(12, 12) + Dot(6, 2) << "\n";
    cout << "������������� �������� * \n<Dot(1, 2) * 10>\n";
    cout << Dot(1, 2) * 10 << "\n";
    cout << "������������� �������� / \n<Dot(12, 12) / 4>\n";
    cout << Dot(12, 12) / 4 << "\n";
    cout << "������������� �������� ��������� == \n<Dot(1, 2) == Dot(1, 2)>\n";
    cout << (Dot(1, 2) == Dot(1, 2) ? "Equal" : "Not equal") << "\n";
    cout << "������������� �������� ��������� != \n<Dot(1, 2) != Dot(1, 3)>\n";
    cout << (Dot(1, 2) != Dot(1, 3) ? "Not equal" : "Equal") << "\n";
    //////////////////// class circle ////////////////////
    /*Circle c1;
    Circle c2(1, 1, 2);
    cout << "By default constructor: x= " << c1.getx() << " y= " << c1.gety() << " rad= " << c1.getrad() << endl;
    cout << "By constructor with parametrs: x= " << c2.getx() << " y= " << c2.gety() << " rad= " << c2.getrad() << endl;
    Circle* cir = new Circle(3, 3, 3);
    delete cir; // ���������� ���������� ��� ������� cir

    int c;
    c1.setx(12);
    c1.sety(13);
    c1.setrad(10);
    c = c1.getx(); cout <<"c1 x = "<< c << endl;
    c = c1.gety(); cout << "c1 y = " << c << endl;
    c = c1.getrad(); cout << "c1 rad = " << c << endl;
    
    c1.moveTo(1, 1);
    cout << c1; // ��������� ������������� <<
    cin >> c2;  // ��������� ������������� >>
    cout << c2;
    if (c1 == c2)
        cout << "c1 and c2 are the same.\n";

    if (c1 != c2)
        cout << "c1 and c2 are not the same.\n ";
    //////////////////// class sector ///////////////////////
    Sector s1;
    Sector s2(2, 3, 6, 2, 3);
    cout << "By default constructor: x= " << s1.getx() << " y= " << s1.gety() << " rad= " << s1.getrad() << " a= " << s1.geta()<< " b= " << s1.getb() << endl;
    cout << "By constructor with parametrs: x= " << s1.getx() << " y= " << s1.gety() << " rad= " << s1.getrad() << " a= " << s1.geta() << " b= " << s1.getb() << endl;
    Sector* sec = new Sector(1, 1, 1, 1, 1);
    delete sec; // ���������� ���������� ��� ������� sec

    int s;
    s1.setx(44);
    s1.sety(45);
    s1.setrad(46);
    s1.seta(47);
    s1.setb(48);
    cout << s1; // ��������� ������������� <<

    s1.moveTo(88, 6.3);
    cout << s1.getx() << endl;
    cout << s1.gety() << endl;

    cin >> s2; // ��������� ������������� >>
    cout << s2;
    if (s1 == s2)
        cout << "s1 and s2 are the same.\n";

    if (s1 != s2)
        cout << "s1 and s2 are not the same.\n ";*/
    getch();
}
//********************************************************************************

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

    //���� ������ ����� ������ ����
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);    
    cout << "1. English\n2. ������� \n3. ���������\n";
    cin >> language;

    int i, j, n;    
    do {
        // ����� ���� �������� ������
        system("cls");              //������� �����
        cout << "----------------------------------------\n";
        cout << menu_locale(1, language);
        cout << "----------------------------------------\n";
        cin >> i;   //������ ������ ������ ����
        switch (i)
        {
        case 1:
            menu2<Fig<Dot>, Dot, FigIterator<Dot>>(dots, dot, dotiter);                      //����� ������� ������ � �������� ������� ��� �����
            break;
        case 2:
            menu2<Fig<Circle>, Circle, FigIterator<Circle>>(circles, circle, circleiter); //����� ������� ������ � �������� ������� ��� ������
            break;
        case 3:
            menu2<Fig<Sector>, Sector, FigIterator<Sector>>(sectors, sector, sectoriter); //����� ������� ������ � �������� ������� ��� ��������
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
            Autotesting();
            break;  
        case 8:
            break;
        default:
            break;
        }
    } while (i != 8);
    
    return 0;
}