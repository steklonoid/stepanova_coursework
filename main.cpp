#include <iostream>
#include <vector>
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

int main()
{   

    Fig<Dot> dots;
    Fig<Circle> circles;
    Fig<Sector> sectors;

    FigIterator<Dot> dotiter = dots.begin();
    FigIterator<Circle> circleiter = circles.begin();
    FigIterator<Sector> sectoriter = sectors.begin();

    int i, j;
    do {
        Dot dot;
        Circle circle;
        Sector sector;
        system("cls");
        cout << "----------------------------------------\n";
        cout << "1. Dots\n2. Circles\n3. Sectors\n4. Exit\n";
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
        default:
            break;

        }

    } while (i != 4);
        
    return 0;
}