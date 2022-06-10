#include <iostream>
#include <fstream>
#include <conio.h>
#include "Dot.h"
#include "Ñircle.h"
#include "Sector.h"
#include "Figura.h"
using namespace std;

template <typename T1, typename T2, typename T3>
void menu2(T1& cont, T2& el, T3& iter, string name)
{   
    int j;
    do {
        system("cls");
        cout << "----------------------------------------\n";
        cout << "1.Add " << name << "\n2.Show all " << name << "s\n3.Delete " << name << " by index\n4.Delete all " << name << "s\n5.Previous menu\n";
        cout << "----------------------------------------\n";        
        cin >> j;
        switch (j)
        {
        case 1:
            cin >> el;
            cont.addEl(el);
            break;
        case 2:
            if (cont.sizearr() == 0)
            {
                cout << " no any " << name << "s";
            }
            else
            {
                iter = cont.begin();
                int counter = 0;
                while (iter != cont.end())
                {
                    counter++;
                    cout << counter << ". " << *iter;
                    iter++;
                }
            }
            getch();
            break;
        case 3:
            int ind;
            cout << "Enter index less then " << cont.sizearr() << "\n";
            cin >> ind;
            if (ind < cont.sizearr() && ind >= 0)
            {
                cont.removeEl(ind);
            }
            break;
        case 4:
            cont.removeAll();
            break;
        case 5:
            break;
        default:
            break;
        }
    } while (j != 5);    
}

template <typename T1, typename T2>
void loaddb(T1& cont, T2& el, string filename)
{
    int n;
    fstream db;
    db.open(filename, ios::in | ios::binary);
    if (db)
    {
        db.read((char*)&n, sizeof(int));        
        for (int i = 0; i < n; i++)
        {
            db.read((char*)&el, sizeof(el));
            cont.addEl(el);
        }
    }
    db.close();    
}

template <typename T1, typename T2, typename T3>
void savedb(T1& cont, T2& el, T3& iter, string filename)
{
    fstream db;
    db.open(filename, ios::out | ios::binary);
    int n = cont.sizearr();
    db.write((char*)&n, sizeof(int));
    iter = cont.begin();
    while (iter != cont.end())
    {
        el = *iter;
        db.write((char*)&el, sizeof(el));
        iter++;
    }
    db.close();
}

int main()
{   
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

    loaddb<Fig<Dot>, Dot>(dots, dot, dotsdb);
    loaddb<Fig<Circle>, Circle>(circles, circle, circlesdb);
    loaddb<Fig<Sector>, Sector>(sectors, sector, sectorsdb);

    int i, n;
    do {
        
        system("cls");
        cout << "----------------------------------------\n";
        cout << "1. Dots\n2. Circles\n3. Sectors\n4. Find circle cluster\n5. Summury info\n6. Save DB\n7. Exit\n";
        cout << "----------------------------------------\n";
        cin >> i;
        switch (i)
        {
        case 1:
            menu2<Fig<Dot>, Dot, FigIterator<Dot>>(dots, dot, dotiter, "dot");
            break;
        case 2:
            menu2<Fig<Circle>, Circle, FigIterator<Circle>>(circles, circle, circleiter, "circle");
            break;
        case 3:
            menu2<Fig<Sector>, Sector, FigIterator<Sector>>(sectors, sector, sectoriter, "sector");
            break;
        case 4:
            break;
        case 5:
            cout << dots.sizearr() << " dots\n";
            cout << circles.sizearr() << " circles\n";
            cout << sectors.sizearr() << " sectors\n";
            getch();
            break;
        case 6:
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