#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;

	pointLightCount = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		printf("Error during creation of shader program!\n");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar errorLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(errorLog), NULL, errorLog);
		printf("Error linking: '%s'\n", errorLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(errorLog), NULL, errorLog);
		printf("Error validating: '%s'\n", errorLog);
		return;
	}

	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

	uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	uniformDirectionalLight.uniformSpecularIntensity = glGetUniformLocation(shaderID, "directionalLight.base.specularIntensity");

	uniformMaterial.uniformAmbientIntensity = glGetUniformLocation(shaderID, "material.ambientIntensity");
	uniformMaterial.uniformAmbientColour = glGetUniformLocation(shaderID, "material.ambientColour");
	uniformMaterial.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "material.diffuseIntensity");
	uniformMaterial.uniformDiffuseColour = glGetUniformLocation(shaderID, "material.diffuseColour");
	uniformMaterial.uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
	uniformMaterial.uniformSpecularColour = glGetUniformLocation(shaderID, "material.specularColour");
	uniformMaterial.uniformShininess = glGetUniformLocation(shaderID, "material.shininess");


	uniformPointLight.uniformColour = glGetUniformLocation(shaderID, "pointLight.base.colour");
	uniformPointLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "pointLight.base.ambientIntensity");
	uniformPointLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "pointLight.base.diffuseIntensity");
	uniformPointLight.uniformSpecularIntensity = glGetUniformLocation(shaderID, "pointLight.base.specularIntensity");
	uniformPointLight.uniformPosition = glGetUniformLocation(shaderID, "pointLight.position");
	uniformPointLight.uniformConstant = glGetUniformLocation(shaderID, "pointLight.constant");
	uniformPointLight.uniformLinear = glGetUniformLocation(shaderID, "pointLight.linear");
	uniformPointLight.uniformExponent = glGetUniformLocation(shaderID, "pointLight.exponent");
}

GLuint Shader::GetProjectionLocation()
{
	return uniformProjection;
}
GLuint Shader::GetModelLocation()
{
	return uniformModel;
}
GLuint Shader::GetViewLocation()
{
	return uniformView;
}
GLuint Shader::GetMaterialAmbientIntensityLocation()
{
	return uniformMaterial.uniformAmbientIntensity;
}
GLuint Shader::GetMaterialAmbientColourLocation()
{
	return uniformMaterial.uniformAmbientColour;
}
GLuint Shader::GetMaterialDiffuseIntensityLocation()
{
	return uniformMaterial.uniformDiffuseIntensity;
}
GLuint Shader::GetMaterialDiffuseColourLocation()
{
	return uniformMaterial.uniformDiffuseColour;
}
GLuint Shader::GetMaterialSpecularIntensityLocation()
{
	return uniformMaterial.uniformSpecularIntensity;
}
GLuint Shader::GetMaterialSpecularColourLocation()
{
	return uniformMaterial.uniformSpecularColour;
}
GLuint Shader::GetMaterialShininessLocation()
{
	return uniformMaterial.uniformShininess;
}
GLuint Shader::GetEyePositionLocation()
{
	return uniformEyePosition;
}

void Shader::SetDirectionalLight(DirectionalLight* dLight)
{
	dLight->UseLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColour,
		uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformSpecularIntensity, uniformDirectionalLight.uniformDirection);
}

void Shader::SetPointLight(PointLight* pLight)
{
	pLight->UseLight(uniformPointLight.uniformAmbientIntensity, uniformPointLight.uniformColour,
		uniformPointLight.uniformDiffuseIntensity, uniformPointLight.uniformSpecularIntensity, uniformPointLight.uniformPosition,
		uniformPointLight.uniformConstant, uniformPointLight.uniformLinear, uniformPointLight.uniformExponent);
}

void Shader::UseShader()
{
	glUseProgram(shaderID);
}

void Shader::ClearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}


void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

Shader::~Shader()
{
	ClearShader();
}
