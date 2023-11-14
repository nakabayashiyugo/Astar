#include <iostream>
#include "Map.h"

int main()
{
	Map* pMap = new Map(8, 9);

	pMap->Serth();
	pMap->PrintMap();

	delete pMap;

	return 0;
}