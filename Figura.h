#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Dot.h"
#include "�ircle.h"
#include "Sector.h"
using namespace std;
class DotArray
{
protected:
	vector <Dot> dots;
};
class CircleArray
{
protected:
	vector <Circle> circles;
};
class SectorArray
{
protected:
	vector <Sector> sectors;
};
