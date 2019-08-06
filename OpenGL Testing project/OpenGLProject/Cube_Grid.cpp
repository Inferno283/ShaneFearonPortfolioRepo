#include "Cube_Grid.h"

Cube_Grid::Cube_Grid(int numVerts, Cube_Grid_Vertex *verts, int numCubes, Cube_Grid_Cube *cubes)
{
	// the ISO-surface threshold value
	threshold = 3.0f;
}


Cube_Grid::~Cube_Grid()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

bool Cube_Grid::init(Cube_Grid *grid, int gridSize)
{
	if (createMemory(grid))
	{
		int i, j, k;//values used for creating positions
		int currentCube;//selected cube index
		int currentVertex = 0;//selected vertex within that cube, 8 vertices in a cube
		grid->numVertices = (gridSize + 1)*(gridSize + 1)*(gridSize + 1);
		//assigns positions to vertices
		for (i = 0; i < gridSize + 1; i++) {
			for (j = 0; j < gridSize + 1; j++) {
				for (k = 0; k < gridSize + 1; k++) {
					grid->vertices[currentVertex].position.x = (i*30.0f) / (gridSize)-15.0f;
					grid->vertices[currentVertex].position.y = (j*30.0f) / (gridSize)-15.0f;
					grid->vertices[currentVertex].position.z = (k*30.0f) / (gridSize)-15.0f;
					currentVertex++;
				}
			}
		}

		grid->numCubes = (gridSize)*(gridSize)*(gridSize);
		currentCube = 0;
		//assign vertices to cubes
		for (i = 0; i < gridSize; i++) {
			for (j = 0; j < gridSize; j++) {
				for (k = 0; k < gridSize; k++) {
					grid->cubes[currentCube].vertices[0] = &grid->vertices[(i*(gridSize + 1) + j)*(gridSize + 1) + k];
					grid->cubes[currentCube].vertices[1] = &grid->vertices[(i*(gridSize + 1) + j)*(gridSize + 1) + k + 1];
					grid->cubes[currentCube].vertices[2] = &grid->vertices[(i*(gridSize + 1) + (j + 1))*(gridSize + 1) + k + 1];
					grid->cubes[currentCube].vertices[3] = &grid->vertices[(i*(gridSize + 1) + (j + 1))*(gridSize + 1) + k];
					grid->cubes[currentCube].vertices[4] = &grid->vertices[((i + 1)*(gridSize + 1) + j)*(gridSize + 1) + k];
					grid->cubes[currentCube].vertices[5] = &grid->vertices[((i + 1)*(gridSize + 1) + j)*(gridSize + 1) + k + 1];
					grid->cubes[currentCube].vertices[6] = &grid->vertices[((i + 1)*(gridSize + 1) + (j + 1))*(gridSize + 1) + k + 1];
					grid->cubes[currentCube].vertices[7] = &grid->vertices[((i + 1)*(gridSize + 1) + (j + 1))*(gridSize + 1) + k];
					currentCube++;
				}
			}
		}
		return true;
	}
	else
		return false;
}



bool Cube_Grid::createMemory(Cube_Grid *grid)
{
	grid->vertices = (Cube_Grid_Vertex *)malloc(sizeof(Cube_Grid_Vertex)*(GridSize + 1)*(GridSize + 1)*(GridSize + 1));
	if (!grid->vertices) { return false; }
	grid->cubes = (Cube_Grid_Cube *)malloc(sizeof(Cube_Grid_Cube)*GridSize*GridSize*GridSize);
	if (!grid->cubes) { return false; }
	return true;
}

void Cube_Grid::drawSurface(Cube_Grid * grid, float threshold, Shader *cubeGridShader, Transform t, bool wireframe)
{
	int i, k, currentEdge;
	int usedEdges;
	float delta;
	static Surface_Vertex edgeVertices[12];

	//loop through cubes
	for (i = 0; i<grid->numCubes; i++) {
		//calculate which vertices are inside the surface
		unsigned char cubeIndex = 0;
		if (grid->cubes[i].vertices[0]->value < threshold)
			cubeIndex |= 1;//bitwise OR Assignment
		if (grid->cubes[i].vertices[1]->value < threshold)
			cubeIndex |= 2;
		if (grid->cubes[i].vertices[2]->value < threshold)
			cubeIndex |= 4;
		if (grid->cubes[i].vertices[3]->value < threshold)
			cubeIndex |= 8;
		if (grid->cubes[i].vertices[4]->value < threshold)
			cubeIndex |= 16;
		if (grid->cubes[i].vertices[5]->value < threshold)
			cubeIndex |= 32;
		if (grid->cubes[i].vertices[6]->value < threshold)
			cubeIndex |= 64;
		if (grid->cubes[i].vertices[7]->value < threshold)
			cubeIndex |= 128;
		//look this value up in the edge table to see which edges to interpolate along
		usedEdges = edgeTable[cubeIndex];
		//if the cube is entirely within/outside surface, no faces   
		if (usedEdges == 0 || usedEdges == 255)continue;

		//update these edges
		for (currentEdge = 0; currentEdge<12; currentEdge++) {
			if (usedEdges & 1 << currentEdge) {
				Cube_Grid_Vertex * v1 = grid->cubes[i].vertices[CubeEdgeVertices[currentEdge * 2]];
				Cube_Grid_Vertex * v2 = grid->cubes[i].vertices[CubeEdgeVertices[currentEdge * 2 + 1]];
				delta = (threshold - v1->value) / (v2->value - v1->value);
				edgeVertices[currentEdge].position.x = v1->position.x + delta*(v2->position.x - v1->position.x);
				edgeVertices[currentEdge].position.y = v1->position.y + delta*(v2->position.y - v1->position.y);
				edgeVertices[currentEdge].position.z = v1->position.z + delta*(v2->position.z - v1->position.z);
				edgeVertices[currentEdge].normal.x = v1->normal.x + delta*(v2->normal.x - v1->normal.x);
				edgeVertices[currentEdge].normal.y = v1->normal.y + delta*(v2->normal.y - v1->normal.y);
				edgeVertices[currentEdge].normal.z = v1->normal.z + delta*(v2->normal.z - v1->normal.z);
			}
		}
		//Put Vertices into a vector for further processing
		for (k = 0; triTable[cubeIndex][k] != -1; k += 3) {
			addVertices(edgeVertices[triTable[cubeIndex][k + 0]].normal, edgeVertices[triTable[cubeIndex][k + 0]].position);
			addVertices(edgeVertices[triTable[cubeIndex][k + 2]].normal, edgeVertices[triTable[cubeIndex][k + 2]].position);
			addVertices(edgeVertices[triTable[cubeIndex][k + 1]].normal, edgeVertices[triTable[cubeIndex][k + 1]].position);
		}
	}

	glDisable(GL_TEXTURE_2D);
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	//put surface vertices into buffer for further processing in Shaders
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, surfaceVertices.size() * sizeof(glm::vec3), surfaceVertices.data(), GL_DYNAMIC_DRAW);//SURFACE VERTICES!!!

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//normals
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, surfaceNormals.size() * sizeof(glm::vec3), surfaceNormals.data(), GL_DYNAMIC_DRAW);//SURFACE NORMALS!!!

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	if (wireframe)
	{
		//if wireframe is selected
		glPolygonMode(GL_FRONT, GL_LINE);  // enable wireframe
		glDrawArrays(GL_TRIANGLES, 0, surfaceVertices.size());
		glPolygonMode(GL_FRONT, GL_FILL);  // revert to solid shading(for rest of scene)
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, surfaceVertices.size());
	}
	
	surfaceNormals.clear();
	surfaceVertices.clear();
	glBindVertexArray(0);
	}

void Cube_Grid::addVertices(glm::vec3 normal, glm::vec3 vertex)
{
	//Adds vertices to the surface
	surfaceNormals.push_back(normal);
	surfaceVertices.push_back(vertex);
}
