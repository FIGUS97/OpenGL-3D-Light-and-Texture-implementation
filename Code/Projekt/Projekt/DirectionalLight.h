#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>

class DirectionalLight
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity, GLfloat sIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
		GLfloat diffuseIntensityLocation, GLfloat specularIntensityLocation, GLfloat directionLocation);
	void updateAmbientIntensity(GLfloat aIntensity);
	void updateDiffuseIntensity(GLfloat dIntensity);
	void updateSpecularIntensity(GLfloat sIntensity);
	void updateColour(glm::vec3 colourVector);

	~DirectionalLight();

private:
	glm::vec3 direction;

	glm::vec3 colour;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
	GLfloat specularIntensity;
};

