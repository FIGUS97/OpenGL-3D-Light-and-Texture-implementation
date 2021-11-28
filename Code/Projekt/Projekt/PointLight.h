#pragma once
//#include "Light.h"
#include <GL\glew.h>
#include <glm\glm.hpp>

class PointLight
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity, GLfloat sIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat con, GLfloat lin, GLfloat exp);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
		GLfloat diffuseIntensityLocation, GLfloat specularIntensityLocation, GLfloat positionLocation,
		GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation);

	void setPointLightPos(GLfloat xPos, GLfloat yPos, GLfloat zPos);
	void updateLoopPointLightPos(GLfloat lightSpeedVelocity);
	void updatePointLightFactors(GLfloat exp, GLfloat lin, GLfloat constant);
	void updateAmbientIntensity(GLfloat aIntensity);
	void updateDiffuseIntensity(GLfloat dIntensity);
	void updateSpecularIntensity(GLfloat sIntensity);
	void updateColour(glm::vec3 colourVector);
	glm::vec3 getPointLightPos();

	~PointLight();

private:
	glm::vec3 position;

	glm::vec3 colour;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
	GLfloat specularIntensity;

	GLfloat constant, linear, exponent;
};

