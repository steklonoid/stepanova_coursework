#include <iostream>
#include <vector>
#include <conio.h>
#include "Dot.h"
using namespace std;

int main()
{   
    Dot dot1(5, 6);
    cout << dot1.getx() << " " << dot1.gety() << "\n";
    dot1.moveTo(7.5, 20);
    cout << dot1.getx() << " " << dot1.gety() << "\n";
    Dot dot2 = dot1;
    cout << dot2.getx() << " " << dot2.gety() << "\n";
    getch();
    return 0;
}

