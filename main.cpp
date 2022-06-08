#include <iostream>
#include <vector>
#include <conio.h>
#include "Dot.h"
#include "Ñircle.h"
#include "Sector.h"
using namespace std;

int main()
{   
    Dot dot1(5, 6);
    cout << dot1.getx() << " " << dot1.gety() << "\n";
    dot1.moveTo(7.5, 20);
    cout << dot1.getx() << " " << dot1.gety() << "\n";
    Dot dot2 = dot1;
    cout << dot2.getx() << " " << dot2.gety() << "\n";

    cout << "///////" << endl;
    Circle cir1;
    cir1.setrad(18);    
    cout << "cir1 " << cir1 << "\n";
    Sector sec1(1, 2, 3, 12, 13);
    cout << "alfa - " << sec1.geta() << endl;
    cout << "beta - " << sec1.getb() << endl;
    cout <<"sec1 " << sec1.getx() << "\n";
    
   Dot dot3;
   dot3 = dot1 + dot2;
   cout << "dot3 - " << dot3 << "\n";
   dot3 = dot1 - dot2;
   cout << "dot3 - " << dot3 << "\n";
   dot3 = dot1 * 5;
   cout << "dot3 - " << dot3 << "\n";

    getch();
    
    return 0;
}