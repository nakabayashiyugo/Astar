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
	bool isway;
};

struct math
{
	int x;
	int y;
};

const int dir_Vertical[4] = { 1, 0, -1, 0 };
const int dir_Beside[4] = { 0, 1, 0, -1 };

class Map
{
	std::vector<std::vector<AstarTable>> map_;

	math curMath_;

	math StartMath;
	math GoalMath;
public:
	Map();

	void Serth();
	void PrintMap();
	void SetStartMathX(int x, int y) { StartMath = math{ x, y }; }
	void SetGoalMathX(int x, int y) { GoalMath = math{ x, y }; }
};

