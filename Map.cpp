#include "Map.h"
#include "Laby.h"

Map::Map()
{
	int x, y;
	std::cout << "マスの数入力" << std::endl;
	std::cout << "x : ";
	std::cin >> x;
	std::cout << "y : ";
	std::cin >> y;
	std::cout << std::endl;
	std::cout << "スタート位置入力" << std::endl;
	do
	{
		std::cout << "startX : ";
		std::cin >> StartMath.x;
		std::cout << "startY : ";
		std::cin >> StartMath.y;
	} while (StartMath.x < 0 || StartMath.x >= x || StartMath.y < 0 || StartMath.y >= y);
	std::cout << std::endl;
	std::cout << "ゴール位置入力" << std::endl;
	do
	{
		std::cout << "goalX : ";
		std::cin >> GoalMath.x;
		std::cout << "goalY : ";
		std::cin >> GoalMath.y;
	} while (GoalMath.x < 0 || GoalMath.x >= x || GoalMath.y < 0 || GoalMath.y >= y);
	std::cout << std::endl;


	map_.resize(y);
	for (int i = 0; i < map_.size(); i++)
	{
		map_.at(i).resize(x);
	}

	Laby *laby = new Laby();
	laby->Initialize(x, y);
	laby->Expansion();
	for (int i = 0; i < map_.size(); i++)
	{
		for (int j = 0; j < map_.at(i).size(); j++)
		{
			map_.at(i).at(j).table = laby->GetTable(i, j);
			map_.at(i).at(j).G = 0;
			map_.at(i).at(j).H = (GoalMath.y - i) * (GoalMath.y - i) + (GoalMath.x - j) * (GoalMath.x - j);
			map_.at(i).at(j).F = -1;
			map_.at(i).at(j).isway = false;
			map_.at(i).at(j).isstop = false;
		}
	}
	curMath_ = StartMath;
	map_[StartMath.y][StartMath.x].F = 999;
	map_[StartMath.y][StartMath.x].table = 0;
	map_[GoalMath.y][GoalMath.x].F = -999;
	map_[GoalMath.y][GoalMath.x].table = 0;

	delete laby;
}

void Map::Serth()
{
	
	int cost = 1;
	
	while (true)
	{
		math prevMath = curMath_;
		
		for (int i = 0; i < 4; i++)
		{
			int calcMathX = curMath_.x;
			int calcMathY = curMath_.y;
			if (calcMathY + dir_Vertical[i] >= 0 && calcMathY + dir_Vertical[i] < map_.size() &&
				map_[calcMathY + dir_Vertical[i]][calcMathX].table == 0)
				calcMathY += dir_Vertical[i];
			else continue;
			if (calcMathX + dir_Beside[i] >= 0 && calcMathX + dir_Beside[i] < map_.at(0).size() &&
				map_[calcMathY][calcMathX + dir_Beside[i]].table == 0)
				calcMathX += dir_Beside[i];
			else continue;

			if (map_[calcMathY][calcMathX].F < 0)
			{
				map_[calcMathY][calcMathX].G = cost;
				map_[calcMathY][calcMathX].F = map_[calcMathY][calcMathX].G + map_[calcMathY][calcMathX].H;
			}
		}
		for (int i = 0; i < map_.size(); i++)
		{
			for (int j = 0; j < map_.at(i).size(); j++)
			{
				if (map_[i][j].F >= 0 && (i != StartMath.y || j != StartMath.x))
				{
					if (map_[curMath_.y][curMath_.x].F > map_[i][j].F)
					{
						curMath_.y = i;
						curMath_.x = j;
					}
					else if (map_[curMath_.y][curMath_.x].F == map_[i][j].F)
					{
						if (map_[curMath_.y][curMath_.x].H >= map_[i][j].H)
						{
							curMath_.y = i;
							curMath_.x = j;
						}
					}
				}
			}
		}

		if (prevMath.x == curMath_.x && prevMath.y == curMath_.y)
		{
			map_[prevMath.y][prevMath.x].F = 999;
			//map_[prevMath.y].erase(map_[prevMath.y].begin() + prevMath.x);
		}
		else
		{
			cost++;
		}

		std::cout << "座標 : (" << curMath_.x << ", " << curMath_.y << ")" << std::endl;
		std::cout << "座標 : (" << prevMath.x << ", " << prevMath.y << ")" << std::endl;

		if (curMath_.x == GoalMath.x && curMath_.y == GoalMath.y)
		{
			break;
		}
		PrintMap();
	}
	curMath_ = GoalMath;
	while (true)
	{
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

			static int tmp = -1;
			if (tmp < map_[calcMathY][calcMathX].G)
			{
				curMath_.x = calcMathX;
				curMath_.y = calcMathY;
				tmp = map_[calcMathY][calcMathX].G;
			}
		}
		map_[curMath_.y][curMath_.x].isway = true;

		if (curMath_.x == StartMath.x && curMath_.y == StartMath.y)
		{
			break;
		}
	}
}

void Map::PrintMap()
{
	for (int n = 0; n < map_.size() * 4 + 2; n++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;
	for (int i = 0; i < map_.size(); i++)
	{
		std::cout << "|";
		for (int j = 0; j < map_.at(i).size(); j++)
		{
			printf("%3d", map_.at(i).at(j).F);
			std::cout << "|";
		}
		std::cout << std::endl;
		for (int n = 0; n < map_.size() * 4 + 2; n++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int n = 0; n < map_.size() * 4 + 2; n++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;
	for (int i = 0; i < map_.size(); i++)
	{
		std::cout << "|";
		for (int j = 0; j < map_.at(i).size(); j++)
		{
			printf("%3d", map_.at(i).at(j).G);
			std::cout << "|";
		}
		std::cout << std::endl;
		for (int n = 0; n < map_.size() * 4 + 2; n++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	/*for (int n = 0; n < map_.size() * 4 + 2; n++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;
	for (int i = 0; i < map_.size(); i++)
	{
		std::cout << "|";
		for (int j = 0; j < map_.at(i).size(); j++)
		{
			printf("%3d", map_.at(i).at(j).H);
			std::cout << "|";
		}
		std::cout << std::endl;
		for (int n = 0; n < map_.size() * 4 + 2; n++)
		{
			std::cout << "-";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
*/

	std::cout << std::endl;
	for (int i = 0; i < map_.size(); i++)
	{
		for (int j = 0; j < map_.at(i).size(); j++)
		{
			switch (map_[i][j].table)
			{
			case 0:
				if (i == StartMath.y && j == StartMath.x)
				{
					std::cout << "Ｓ";
				}
				else if (i == GoalMath.y && j == GoalMath.x)
				{
					std::cout << "Ｇ";
				}
				else if (map_[i][j].isway == true)
				{
					std::cout << "◆";
				}
				else
				{
					std::cout << "□";
				}
				break;
			case 1:
				std::cout << "■";
				break;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
