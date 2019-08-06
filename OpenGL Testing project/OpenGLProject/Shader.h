#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <GL/glew.h>
#include "Transform.h"
#include "Camera.h"
#include "Light.h"


class Shader
{
public:
	Shader(const std::string& fileName);

	Shader(const std::string & fileName, bool x);

	void Bind();
	void Update(const Transform & transform, const Camera & camera, glm::vec3 lightPos, glm::vec3 lightcolour, glm::vec3 objectColour);
	//void Update(const Transform & transform, const Camera & camera, glm::vec3 lightPos, glm::vec3 lightcolour, glm::vec4 objectColour);
	//void Update(const Transform & transform, const Camera & camera, glm::vec3 lightPos, glm::vec4 fragColour);
	//void Update(const Transform & transform, const Camera & camera, glm::vec3 lightPos);
	void Update(const Transform& transform, const Camera& camera);
	void Update(const Camera& camera);
	void UpdateReflection(const Transform& transform, const Camera& camera);
	void UpdateCubeGrid(const Transform & transform);
	void UpdateCubeGrid(const Transform & transform, const Camera & camera);
	GLuint getProgram() { return m_program; }
	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator =(const Shader& other) {}

	enum
	{
		TRANSFORM_U,
		PROJECTION_U,
		VIEW_U,
		SKYBOXSAMPLE_U,
		LIGHTPOS_U,
		OBJCOLOUR_U,
		LIGHTCOLOUR_U,
		VIEWPOS_U,

		NUM_UNIFORMS
	};
	
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif SHADER_H