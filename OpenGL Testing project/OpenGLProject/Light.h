#ifndef LIGHT
#define LIGHT
#include <glm\glm.hpp>

class Light
{
public:
	glm::vec3 pos;
	float strength;
	glm::vec4 colour;
	Light();
	Light(glm::vec3 pos, float strength, glm::vec4 colour);
	~Light();
};


#endif // !LIGHT
