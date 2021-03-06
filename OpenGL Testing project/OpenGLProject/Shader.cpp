#include "Shader.h"
#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName+".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName+".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

Shader::Shader(const std::string& fileName, bool metaball)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "modelMatrix");
	m_uniforms[LIGHTPOS_U] = glGetUniformLocation(m_program, "lightPos");
	m_uniforms[OBJCOLOUR_U] = glGetUniformLocation(m_program, "objectColour");
	m_uniforms[LIGHTCOLOUR_U] = glGetUniformLocation(m_program, "lightColour");
	m_uniforms[VIEWPOS_U] = glGetUniformLocation(m_program, "viewPos");
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}

void Shader::Bind() 
{
	glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera, glm::vec3 lightPos, glm::vec3 lightcolour, glm::vec3 objectColour)
{
	glm::mat4 model = camera.GetViewProjection()*transform.GetModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniform3f(m_uniforms[LIGHTPOS_U], lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(m_uniforms[OBJCOLOUR_U], objectColour.x, objectColour.y, objectColour.z);
	glUniform3f(m_uniforms[LIGHTCOLOUR_U], lightcolour.x, lightcolour.y, lightcolour.z);
	glUniform3f(m_uniforms[VIEWPOS_U], camera.GetPos().x, camera.GetPos().y, camera.GetPos().z);
}

void Shader::Update(const Transform & transform, const Camera & camera)
{
	glm::mat4 model = camera.GetViewProjection() *transform.GetModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

void Shader::Update(const Camera& camera)
{
	//Update Skybox
	glm::mat4 view = camera.GetViewMatrixSkybox();
	glm::mat4 projection = camera.GetProjection();
	glUniformMatrix4fv(glGetUniformLocation(m_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void Shader::UpdateReflection(const Transform& transform, const Camera& camera )
{
	glm::mat4 model= transform.GetModel();
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = camera.GetProjection();
	glUniformMatrix4fv(glGetUniformLocation(m_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(glGetUniformLocation(m_program, "cameraPos"), 1, glm::value_ptr(camera.GetPos()));
	glUniform1i(glGetUniformLocation(m_program, "skybox"), 0);//?
	
}

void Shader::UpdateCubeGrid(const Transform& transform)
{
	glm::mat4 model = transform.GetModel();
	glUniformMatrix4fv(glGetUniformLocation(m_program, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0) 
		std::cerr << "error: Shader creation failed!" << std::endl;
	
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader Compilation failed: ");

	return shader;
}

static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open()) 
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load Shader: " << fileName << std::endl;
	}
	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };
	
	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if(success == GL_FALSE)
	{
		if (isProgram) 
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}