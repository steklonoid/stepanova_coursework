#include <iostream>
#include <vector>
#include <conio.h>
#include "Dot.h"
#include "Ñircle.h"
#include "Sector.h"
using namespace std;

int main()
{   
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