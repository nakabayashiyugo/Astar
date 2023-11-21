#include <iostream>
#include <vector>

#pragma once
class Laby
{
	std::vector<std::vector<int>> table_;
public:
	Laby() {};
	void Initialize(int x, int y);
	void Expansion();
	int GetTable(int x, int y) { return table_[x][y]; }
};

