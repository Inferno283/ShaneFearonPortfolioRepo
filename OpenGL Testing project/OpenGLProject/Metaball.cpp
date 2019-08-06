#include "Metaball.h"

void Metaball::MetaballInit(Metaball * m, float x, float y, float z, float r2)
{
	m->p.x = x;
	m->p.y = y;
	m->p.z = z;
	m->r2 = r2;
}

void Metaball::Update(Cube_Grid *cubeGrid, int numMetaballs, Metaball metaballs[], float counter)
{
	//update the metaballs position and calculate surface normal vectors
	glm::vec3 b2p; // /from ball centre
	float r2;
	glm::vec3 p;  // working copy of metaball centre
	float scale, d2;
	int i, j;
	float c = 2.0f*(float)cos(counter / 600);


	// position the metaballs - they all lie in one plane
	metaballs[0].p.x = -4.0f*(float)cos(counter / 700) - c;
	metaballs[0].p.y = 4.0f*(float)sin(counter / 600) - c;
	metaballs[1].p.x = 5.0f*(float)sin(counter / 400) + c;
	metaballs[1].p.y = 5.0f*(float)cos(counter / 400) - c;
	metaballs[2].p.x = -5.0f*(float)cos(counter / 400) - 0.2f*(float)sin(counter / 600);
	metaballs[2].p.y = 5.0f*(float)sin(counter / 500) - 0.2f*(float)sin(counter / 400);

	metaballs[3].p.x = 6.0f*(float)sin(counter / 900) + c;
	metaballs[3].p.y = 6.0f*(float)cos(counter / 900) - c;

	//clear the field
	for (i = 0; i<cubeGrid->numVertices; i++) {
		cubeGrid->vertices[i].value = 0.0f;
		cubeGrid->vertices[i].normal.x = 0.0;
		cubeGrid->vertices[i].normal.y = 0.0;
		cubeGrid->vertices[i].normal.z = 0.0;
	}

	//evaluate the scalar field at each point
	for (i = 0; i<numMetaballs; i++) {
		r2 = metaballs[i].r2;//field strength
		p = metaballs[i].p;
		for (j = 0; j<cubeGrid->numVertices; j++) {
			b2p.x = cubeGrid->vertices[j].position.x - p.x;
			b2p.y = cubeGrid->vertices[j].position.y - p.y;
			b2p.z = cubeGrid->vertices[j].position.z - p.z;
			//get squared distance from metaball ball centre to cube corner
			d2 = b2p.x*b2p.x + b2p.y*b2p.y + b2p.z*b2p.z;
			if (d2 == 0.0f)d2 = 0.0001f;//clamping
			cubeGrid->vertices[j].value += r2 / d2;
			scale = r2 / (d2*d2);
			cubeGrid->vertices[j].normal.x += b2p.x*scale;
			cubeGrid->vertices[j].normal.y += b2p.y*scale;
			cubeGrid->vertices[j].normal.z += b2p.z*scale;
		}
	}
}
