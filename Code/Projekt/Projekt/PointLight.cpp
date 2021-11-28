#include "PointLight.h"



PointLight::PointLight()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity, GLfloat sIntensity,
	GLfloat xPos, GLfloat yPos, GLfloat zPos,
	GLfloat con, GLfloat lin, GLfloat exp)
{
	position = glm::vec3(xPos, yPos, zPos);
	constant = con;
	linear = lin;
	exponent = exp;
	colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
	specularIntensity = sIntensity;
}

void PointLight::setPointLightPos(GLfloat xPos, GLfloat yPos, GLfloat zPos)
{
	position = glm::vec3(xPos, yPos, zPos);
}

void PointLight::updateLoopPointLightPos(GLfloat currentAngle)
{
	currentAngle = currentAngle * 3.14159265f / 180.0f;
	GLfloat radius = glm::length(position - glm::vec3(0.0f, position.y, 0.0f));

	position = glm::vec3(position.x * glm::cos(currentAngle) - position.z * glm::sin(currentAngle), position.y, position.x * glm::sin(currentAngle) + position.z * glm::cos(currentAngle));

	//printf("%f %f %f %f\n", position.x, position.y, position.z, radius);
}

void PointLight::updateAmbientIntensity(GLfloat aIntensity)
{
	ambientIntensity = aIntensity;
}

void PointLight::updateDiffuseIntensity(GLfloat dIntensity)
{
	diffuseIntensity = dIntensity;
}

void PointLight::updateSpecularIntensity(GLfloat sIntensity)
{
	specularIntensity = sIntensity;
}

void PointLight::updateColour(glm::vec3 colourVector)
{
	colour = colourVector;
}

void PointLight::updatePointLightFactors(GLfloat exp, GLfloat lin, GLfloat con)
{
	exponent = exp;
	linear = lin;
	constant = con;
}

glm::vec3 PointLight::getPointLightPos()
{
	return position;
}



void PointLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
	GLfloat diffuseIntensityLocation, GLfloat specularIntensityLocation, GLfloat positionLocation,
	GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform1f(specularIntensityLocation, specularIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);
}

PointLight::~PointLight()
{
}
