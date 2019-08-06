#ifndef SURFACE_VERTEX
#define SURFACE_VERTEX
#include <glm/glm.hpp>
class Surface_Vertex
{
	// vertex created from linear interpolation along the edge
public:
	glm::vec3 position;
	glm::vec3 normal;//
	Surface_Vertex();
	~Surface_Vertex();
};

#endif