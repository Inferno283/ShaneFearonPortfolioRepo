#ifndef CUBE_GRID_VERTEX
#define CUBE_GRID_VERTEX
#include <glm/glm.hpp>
class Cube_Grid_Vertex
{
public:
	glm::vec3 position;//pos of the grid vertex
	glm::vec3 normal;
	float value;//Value of the scalar field
	Cube_Grid_Vertex();
	~Cube_Grid_Vertex();
};

#endif