#ifndef METABALL_H
#define METABALL_H
#include <glm\glm.hpp>
#include "Cube_Grid.h"
#include "Timer.h"

struct Metaball
{
	glm::vec3 p;
	float r2;
	void MetaballInit(Metaball *m, float x, float y, float z, float r2);
	void Update(Cube_Grid * cubeGrid, int numMetaballs, Metaball metaballs[], float counter);
};

#endif