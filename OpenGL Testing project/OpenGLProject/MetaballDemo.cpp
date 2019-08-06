#include "MetaballDemo.h"


MetaballDemo::MetaballDemo()
{
	DemoInit();
}


MetaballDemo::~MetaballDemo()
{
}

void MetaballDemo::Draw()
{
}

bool MetaballDemo::DemoInit()
{
	cubeGrid = { 0,NULL,0,NULL };
	int i;
	if (!cubeGrid.CubeGrid_CreateMemory(&cubeGrid))
		return false;
	if (!cubeGrid.CubeGrid_Init(&cubeGrid, NUMBER_GRIDSIZE))
		return false;
	for (i = 0; i<NUMBER_METABALLS; i++)
		metaballs[i].MetaballInit(&metaballs[i], 0.0f, 0.0f, 0.0f, 5.0f + (float)i);
	Time_Reset();
	return true;
}
