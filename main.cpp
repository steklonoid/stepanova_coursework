#include <iostream>
#include <vector>
#include <conio.h>
#include "Dot.h"
using namespace std;

int main()
{   
    Dot dot;
    dot.moveTo(7.5, 20);
    cout << dot.get_x() << " " << dot.get_y();
    getch();
    return 0;
}

