#include <iostream>
#include <vector>
#include <conio.h>
#include "Dot.h"
#include "Ñircle.h"
#include "Sector.h"
#include "Figura.h"
using namespace std;

int main()
{   

    Fig<Dot> dots;
    Fig<Circle> circles;
    Fig<Sector> sectors;

    int i, j;
    do {
        system("cls");
        cout << "----------------------------------------\n";
        cout << "1. Dots\n2. Circles\n3. Sectors\n4. Exit\n";
        cout << "----------------------------------------\n";
        cin >> i;
        switch (i)
        {
        case 1:
            do {
                system("cls");
                cout << "----------------------------------------\n";
                cout << "1. Add Dot\n2. Show all dots\n3. Delete dot by index\n4. Delete all dots\n5. Previous menu\n";
                cout << "----------------------------------------\n";
                cin >> j;
                switch (j)
                {
                case 1:
                    break;
                case 2:
                    if (dots.sizearr() == 0)
                    {
                        cout << " no any dots";
                    }
                    else
                    {

                    }
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                default:
                    break;
                }
            } while (j != 5);
            break;
        case 2:
            do {
                system("cls");
                cout << "----------------------------------------\n";
                cout << "1. Add circle\n2. Show all circles\n3. Delete circle by index\n4. Delete all circles\n5. Previous menu\n";
                cout << "----------------------------------------\n";
                cin >> j;
                switch (j)
                {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                default:
                    break;
                }
            } while (j != 5);
            break;
        case 3:
            do {
                system("cls");
                cout << "----------------------------------------\n";
                cout << "1. Add sector\n2. Show all sectors\n3. Delete sector by index\n4. Delete all sectors\n5. Previous menu\n";
                cout << "----------------------------------------\n";
                cin >> j;
                switch (j)
                {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                default:
                    break;
                }
            } while (j != 5);
            break;
        case 4:
            break;
        default:
            break;
        }

    } while (i != 4);
        
    return 0;
}