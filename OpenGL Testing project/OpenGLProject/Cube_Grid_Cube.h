#ifndef CUBE_GRID_CUBE
#define CUBE_GRID_CUBE
#include "Cube_Grid_Vertex.h"
class Cube_Grid_Cube
{
public:
	Cube_Grid_Vertex *vertices[8];//8 pointers to the 8 vertices of the cube
	Cube_Grid_Cube();
	~Cube_Grid_Cube();
};

#endif