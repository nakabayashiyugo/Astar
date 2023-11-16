#include "Map.h"

Map::Map(int _height, int _width)
{
	map_.resize(_height);
	for (int i = 0; i < map_.size(); i++)
	{
		map_.at(i).resize(_width);
	}

	for (int i = 0; i < map_.size(); i++)
	{
		for (int j = 0; j < map_.at(i).size(); j++)
		{
			map_.at(i).at(j).table = 0;
			map_.at(i).at(j).G = 0;
			map_.at(i).at(j).H = (GoalMath.x - i) * (GoalMath.x - i) + (GoalMath.y - j) * (GoalMath.y - j);
			map_.at(i).at(j).F = -1;
		}
	}
	curMath_ = StartMath;
	map_[StartMath.y][StartMath.x].F = 999;
}

void Map::Serth()
{
	int cost = 0;
	
	while (true)
	{
		cost++;
		for (int i = 0; i < 4; i++)
		{
			int calcMathX = curMath_.x;
			int calcMathY = curMath_.y;
			if (calcMathY + dir_Vertical[i] >= 0 && calcMathY + dir_Vertical[i] < map_.size())
				calcMathY += dir_Vertical[i];
			else continue;
			if (calcMathX + dir_Beside[i] >= 0 && calcMathX + dir_Beside[i] < map_.at(0).size())
				calcMathX += dir_Beside[i];
			else continue;

			if (map_[calcMathY][calcMathX].F < 0) map_[calcMathY][calcMathX].G = cost;
			map_[calcMathY][calcMathX].F = map_[calcMathY][calcMathX].G + map_[calcMathY][calcMathX].H;
		}
		for (int i = 0; i < map_.size(); i++)
		{
			for (int j = 0; j < map_.at(i).size(); j++)
			{
				if (map_[i][j].F >= 0 && (i != StartMath.y || j != StartMath.x))
				{
					if (map_[curMath_.y][curMath_.x].F >= map_[i][j].F)
					{
						curMath_.y = i;
						curMath_.x = j;
					}
				}
			}
		}

		if (curMath_.x == GoalMath.x && curMath_.y == GoalMath.y) break;
		PrintMap();
	}
}

void Map::PrintMap()
{
	for (int i = 0; i < map_.size(); i++)
	{
		for (int j = 0; j < map_.at(i).size(); j++)
		{
			std::cout << map_.at(i).at(j).F << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < map_.size(); i++)
	{
		for (int j = 0; j < map_.at(i).size(); j++)
		{
			std::cout << map_.at(i).at(j).G << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
