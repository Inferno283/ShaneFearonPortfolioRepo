#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm\glm.hpp>

class Skybox
{
public:
	Skybox();
	GLuint loadCubemap(std::vector<const GLchar*> faces);
	GLuint& getSkyboxVAO() { return skyboxVAO; }
	GLuint& getSkyboxCubemapTexture() { return cubemapTexture; }
	void draw(GLuint program);
	~Skybox();
protected:
private:
	GLuint skyboxFaces;
	GLuint skyboxVAO, skyboxVBO;
	GLuint cubemapTexture;
};
