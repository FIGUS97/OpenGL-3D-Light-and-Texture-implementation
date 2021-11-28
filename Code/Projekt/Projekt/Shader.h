#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

#include "DirectionalLight.h"
#include "PointLight.h"

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();

	GLuint GetMaterialAmbientIntensityLocation();
	GLuint GetMaterialAmbientColourLocation();

	GLuint GetMaterialDiffuseIntensityLocation();
	GLuint GetMaterialDiffuseColourLocation();

	GLuint GetMaterialSpecularIntensityLocation();
	GLuint GetMaterialSpecularColourLocation();

	GLuint GetMaterialShininessLocation();
	GLuint GetEyePositionLocation();


	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLight(PointLight* pLight);

	void UseShader();
	void ClearShader();

	~Shader();

private:
	int pointLightCount;

	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition;

	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformSpecularIntensity;

		GLuint uniformDirection;
	} uniformDirectionalLight;


	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformSpecularIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLight;

	struct MaterialLocations {
		GLuint uniformAmbientIntensity;
		GLuint uniformAmbientColour;

		GLuint uniformDiffuseIntensity;
		GLuint uniformDiffuseColour;

		GLuint uniformSpecularIntensity;
		GLuint uniformSpecularColour;

		GLuint uniformShininess;
	} uniformMaterial;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

