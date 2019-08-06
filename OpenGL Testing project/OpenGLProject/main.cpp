#include <iostream>
#include "Display.h"
#include <GL/glew.h>
#include "shader.h"
#include "mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "skybox.h"
#include <vector>
#include "Cube_Grid.h"
#include "Cube_Grid_Cube.h"
#include "Cube_Grid_Vertex.h"
#include "Metaball.h"
#include "Light.h"

#define WIDTH 1280
#define HEIGHT 720

int main(int argc, char** argv){
#pragma region INIT
	Display display(WIDTH, HEIGHT, "OpenGL Testing Space");
	
	Mesh monkey("./res/monkey3.obj");
	Mesh sphere("./res/sphere.obj");
	Mesh crate("./res/Crate1.obj");

	Shader basicShader("./res/basicShader");
	Shader skyBoxShader("./res/skyboxShader");
	Shader sphereShader("./res/sphereShader");
	Shader metaballShader("./res/metaBallShader", true);

	Texture monkeyTexture("./res/gun.png");
	Texture crateTexture("./res/crate_1.jpg");

	Skybox skybox;

	Camera camera(glm::vec3(0, 0, -4), 70.05f, (float)WIDTH /(float)HEIGHT, 0.01f, 1000.0f);

	Light light(glm::vec3(3, 20, 10), 5, glm::vec4(1.0,1.0,1.0,1.0));

	Transform transform, transform2, transform3, transform4;
	bool wireframe = false;
	   
	#define numMetaballs  4
	Metaball metaballs[numMetaballs];//Create array to hold Metaballs
	for (int i = 0; i<numMetaballs; i++)
		metaballs->MetaballInit(&metaballs[i], 0.0f, 0.0f, 0.0f, 5.0f + (float)i);//initialise each Metaball
	
	// The cubegrid structure 
	Cube_Grid cubeGrid(0,NULL,0,NULL);
	if (!cubeGrid.init(&cubeGrid, cubeGrid.GridSize))
	{
		std::cout << "SOMETHINGS WRONG - CUBE INIT" << std::endl;
	}

#pragma endregion 
#pragma region GAMELOOP
	float counter = 0.0f;
	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		//Setting transformations
		float sinCounter = sinf(counter*3);
		float cosCounter = cosf(counter*3);
		
		//monkey
		transform.GetPos().x = cosCounter*5;
		transform.GetPos().z = sinCounter*5+4;
		transform.GetRot().y = counter*10;

		//crate
		transform2.GetPos().z = 4;
		transform2.GetRot().x = counter;
		transform2.GetRot().y = 5;

		//Reflective sphere
		transform3.GetPos().x = sinCounter*3;
		transform3.GetPos().z = cosCounter*2+4;

		//Metaball assembly
		transform4.GetPos().x = 20;

		display.Update(&camera, wireframe);//pass in camera for the key movement?
		camera.SetLookAt(camera.m_position, camera.m_forward, camera.m_up);

		//Draw skybox
		glDepthMask(GL_FALSE);
		skyBoxShader.Bind();
		skyBoxShader.Update(camera);
		skybox.draw(skyBoxShader.getProgram());
		glDepthMask(GL_TRUE);

		//Bind shader1 and Texture 1, draw Monkey
		basicShader.Bind();
		monkeyTexture.Bind(0);

		basicShader.Update(transform, camera);
		monkey.Draw();
		
		//Update Shader and draw Crate
		crateTexture.Bind(0);
		basicShader.Update(transform2,camera);
		crate.Draw();
	
		//Bind sphere shader and draw sphere with skybox cubemap reflection
		sphereShader.Bind();
		sphereShader.UpdateReflection(transform3, camera);
		sphere.Draw(skybox.getSkyboxCubemapTexture());
		
		//METABALL AND CUBEGRID
		metaballs->Update(&cubeGrid, numMetaballs, metaballs, counter * 10000);
		metaballShader.Bind();
		glm::vec3 metaballcolour(1.0, 0.0, 0.0);
		metaballShader.Update(transform4, camera, light.pos, light.colour, metaballcolour);
		cubeGrid.drawSurface(&cubeGrid, cubeGrid.threshold, &metaballShader, transform4, wireframe);
		


		display.Update();
		
		counter += 0.005f;
	}
#pragma endregion
	return 0;
}

