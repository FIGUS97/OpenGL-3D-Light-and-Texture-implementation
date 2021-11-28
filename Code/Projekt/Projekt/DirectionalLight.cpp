#include "DirectionalLight.h"


DirectionalLight::DirectionalLight()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity, GLfloat sIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir)
{
	direction = glm::vec3(xDir, yDir, zDir);
	colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
	specularIntensity = sIntensity;
}

void DirectionalLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
	GLfloat diffuseIntensityLocation, GLfloat specularIntensityLocation, GLfloat directionLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform1f(specularIntensityLocation, specularIntensity);
}

void DirectionalLight::updateAmbientIntensity(GLfloat aIntensity)
{
	ambientIntensity = aIntensity;
}

void DirectionalLight::updateDiffuseIntensity(GLfloat dIntensity)
{
	diffuseIntensity = dIntensity;
}

void DirectionalLight::updateSpecularIntensity(GLfloat sIntensity)
{
	specularIntensity = sIntensity;
}

void DirectionalLight::updateColour(glm::vec3 colourVector)
{
	colour = colourVector;
}

DirectionalLight::~DirectionalLight()
{
}
