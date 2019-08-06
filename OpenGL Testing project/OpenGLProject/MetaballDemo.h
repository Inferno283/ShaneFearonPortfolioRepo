#ifndef METABALLDEMO
#define METABALLDEMO
#include "Metaball.h"
#include "cubeGrid.h"
#include "Time.h"
#define NUMBER_METABALLS 4
#define NUMBER_GRIDSIZE 60
float threshold = 1.0f;
class MetaballDemo
{
public:
	Metaball metaballs[NUMBER_METABALLS];
	CubeGrid cubeGrid;
	MetaballDemo();
	~MetaballDemo();
	void Draw();
	bool DemoInit();
	Time t;
};

#endif // !METABALLDEMO