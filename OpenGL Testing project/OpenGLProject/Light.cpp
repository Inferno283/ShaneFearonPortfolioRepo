#include "Light.h"



Light::Light(glm::vec3 pos,  float strength, glm::vec4 colour)
{
	this->pos = pos;
	this->strength = strength;
	this->colour = colour;
}


Light::~Light()
{
}
