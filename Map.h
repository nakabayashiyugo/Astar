#include<iostream>
#include<vector>
#include<cmath>

#pragma once

struct AstarTable
{
	int table;
	int G;
	int H;
	int F;
};

struct math
{
	int x;
	int y;
};

const math StartMath = math{ 0, 0 };
const math GoalMath = math{5, 5};

const int dir_Vertical[4] = { 1, 0, -1, 0 };
const int dir_Beside[4] = { 0, 1, 0, -1 };

class Map
{
	std::vector<std::vector<AstarTable>> map_;

	math curMath_;

public:
	Map(int _height, int _width);

	void Serth();
	void PrintMap();
};

