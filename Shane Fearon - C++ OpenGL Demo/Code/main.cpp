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

#define WIDTH 1280
#define HEIGHT 720

int main(int argc, char** argv){
	Display display(WIDTH, HEIGHT, "OpenGL Testing Space");
	
	Mesh monkey("./res/monkey3.obj");
	Mesh sphere("./res/sphere.obj");
	Mesh crate("./res/Crate1.obj");

	Shader basicShader("./res/basicShader");
	Shader skyBoxShader("./res/skyboxShader");
	Shader sphereShader("./res/sphereShader");

	Texture monkeyTexture("./res/gun.png");
	Texture crateTexture("./res/crate_1.jpg");

	Skybox skybox;

	Camera camera(glm::vec3(0, 0, -4), 70.05f, (float)WIDTH /(float)HEIGHT, 0.01f, 1000.0f);

	Transform transform, transform2, transform3;

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

		camera.SetLookAt(glm::vec3(0, 0, -5), glm::vec3(sinf(counter / 8) / 8, 0, 1), glm::vec3(0, 1, 0));

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
		
		display.Update();
		counter += 0.005f;
	}

	return 0;
}