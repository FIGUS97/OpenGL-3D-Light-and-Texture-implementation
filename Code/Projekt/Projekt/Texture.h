#pragma once

#include <GL\glew.h>

#pragma warning(push, 0)
#include "stb_image.h"
#pragma warning(pop)

class Texture
{
public:
	Texture();
	Texture(char* fileLoc, GLint internalFormat, GLenum format);

	void LoadTexture();
	void UseTexture();
	void ClearTexture();

	~Texture();

private:
	GLuint textureID;
	int width, height, bitDepth;
	GLint texInternalFormat;
	GLenum texFormat;

	char* fileLocation;
};

