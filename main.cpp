#include <iostream>
#include <vector>
#include <conio.h>
#include "Dot.h"
#include "Ñircle.h"
#include "Sector.h"
#include "Figura.h"
using namespace std;

template <class T>
class One
{
public:
    T el;
};



int main()
{   

    Fig<Dot> dots;
    Fig<Circle> circles;
    Fig<Sector> sectors;

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
            One<Dot> one;
            break;
        case 2:            
            break;
        case 3:            
            break;
        case 4:
            break;
        default:
            break;
            /*do {
                system("cls");
                cout << "----------------------------------------\n";
                cout << "1. Add Dot\n2. Show all dots\n3. Delete dot by index\n4. Delete all dots\n5. Previous menu\n";
                cout << "----------------------------------------\n";
                Dot dot;
                cin >> j;
                switch (j)
                {
                case 1:                    
                    cin >> dot;
                    dots.addEl(dot);
                    break;
                case 2:
                    if (dots.sizearr() == 0)
                    {
                        cout << " no any dots";                        
                    }
                    else
                    {
                        FigIterator<Dot> iter = dots.begin();
                        int counter = 0;
                        while (iter != dots.end())
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
                    cout << "Enter index less then " << dots.sizearr() << "\n";
                    cin >> ind;
                    if (ind < dots.sizearr() && ind >= 0)
                    {
                        dots.removeEl(ind);
                    }
                    break;
                case 4:
                    dots.removeAll();
                    break;
                case 5:
                    break;
                default:
                    break;
                }
            } while (j != 5);
            break;*/
        

    } while (i != 4);
        
    return 0;
}