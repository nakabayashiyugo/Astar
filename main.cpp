#include <iostream>
#include "Map.h"

int main()
{
	
	Map* pMap = new Map();

	pMap->Serth();
	pMap->PrintMap();

	delete pMap;

	return 0;
}