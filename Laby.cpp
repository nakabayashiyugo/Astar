#include "Laby.h"

void Laby::Initialize(int x, int y)
{
	table_.resize(y);
	for (int i = 0; i < table_.size(); i++)
	{
		table_.at(i).resize(x);
		for (int j = 0; j < table_.at(i).size(); j++)
		{
			if (i % 2 != 0 && j % 2 != 0)
			{
				table_[i][j] = 1;
			}
		}
	}
}

void Laby::Expansion()
{
	for (int y = 1; y < table_.size() - 1; y++)
	{
		for (int x = 1; x < table_.at(y).size() - 1; x++)
		{
			if (y % 2 != 0 && x % 2 != 0)
			{
				int dirMv = (rand() % 4) + 1;
				switch (dirMv)
				{
				case 1:table_[y][x - 1] = 1; break;
				case 2:table_[y - 1][x] = 1; break;
				case 3:table_[y][x + 1] = 1; break;
				case 4:table_[y + 1][x] = 1; break;
				}
			}
		}
	}
}
