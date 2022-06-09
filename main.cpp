#include <iostream>
#include <vector>
#include <conio.h>
#include "Dot.h"
#include "Ñircle.h"
#include "Sector.h"
using namespace std;

int main()
{   
    int i, j;
    do {
        cout << "----------------------------------------\n";
        cout << "1. Dot\n2. Circle\n3. Sector\n4. Exit\n";
        cout << "----------------------------------------\n";
        cin >> i;
        switch (i)
        {
        case 1:
            do {
               cout << "----------------------------------------\n";
               cout << "1. Add Dot\n2. Show all dots\n3. Delete dot by index\n4. Delete all dots\n5. Previous menu\n";
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
        case 2:
            do {
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

    cout << "------ dots ----------\n";
    Dot dot1(5, 6);
    cout << "dot1 " << dot1 << "\n";
    Dot dot2 = dot1;
    cout << "dot2 " << dot2 << "\n";

    cout << "--------- circle and sector\n";
    Circle cir1;
    cir1.setrad(18);    
    cout << "cir1 " << cir1 << "\n";
    Sector sec1(1, 2, 3, 12, 13);    
    cout <<"sec1 " << sec1 << "\n";
    
    cout << "-------- overrided operators\n";
    Dot dot3;
    dot3 = dot1 + dot2;
    cout << "dot3 - " << dot3 << "\n";
    dot3 = dot1 - dot2;
    cout << "dot3 - " << dot3 << "\n";
    dot3 = dot1 * 5;
    cout << "dot3 - " << dot3 << "\n";

    cout << "------------ overrided polymorph moving\n";
    Dot* p;
    p = &dot2;
    p->moveTo(17, 12);
    cout << "dot2 " << dot2 << "\n";
    p = &cir1;
    p->moveTo(18, 13);
    cout << "cir1 " << cir1 << "\n";
    p = &sec1;
    p->moveTo(19, 14);
    cout << "sec1 " << sec1 << "\n";

    getch();
    
    return 0;
}