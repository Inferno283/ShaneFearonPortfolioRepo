#ifndef CUBEGRID_H
#define CUBEGRID_H
#include <glm/glm.hpp>
#include <GL/glew.h>


typedef struct { // vertex at the corners of the cubes
	glm::vec3 p;
	float  v; //the value of the scalar field at a cube vertes
	glm::vec3 n;
} CubeGridVertex;


// vertex defining the iso-surface mesh p within a cube
// it will lie somewhere along one of the edges of the cube
typedef struct {
	glm::vec3 p;
	glm::vec3 n;
} SurfaceMeshVertex;


typedef struct { // each cube in the lattice is defined by its corner vertices
	CubeGridVertex * vertices[8]; //pointers to vertices around the cube
} CubeGridCube;

struct CubeGrid
{
	int nVertices;   // total number of lattice vertices
	CubeGridVertex * vertices; // list of all lattice cube vertices
	int nCubes;      // total number of lattice cubes
	CubeGridCube * cubes;   // list of all lattice cubes

	bool CubeGrid_CreateMemory(CubeGrid *g);
	bool CubeGrid_Init(CubeGrid *g, int GridSize);
	void CubeGrid_DrawSurface(CubeGrid *g, float threshold);
	void CubeGrid_FreeMemory(CubeGrid *cubegrid);
	void drawTriangleVertex(GLfloat * n, GLfloat * v);
};

#endif