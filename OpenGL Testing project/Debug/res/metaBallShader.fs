#version 330 core

varying vec3 normal0;
varying vec3 FragPos;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 lightColour;
uniform vec4 fragColour;
uniform vec3 viewPos;
uniform vec3 objectColour;

void main()
{
	//ambient calculations
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColour;
	
	//diffuse calculations
	vec3 norm = normalize(normal0);
	vec3 lightDir = normalize(lightPos-FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColour;
	
	//specular calculations
	float specularStrength = 0.7f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColour;
	
	vec3 result = (ambient + diffuse+ specular) * objectColour;
	
	color = vec4(result, 1.0f);
}