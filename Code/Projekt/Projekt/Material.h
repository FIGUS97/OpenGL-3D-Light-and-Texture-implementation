#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "materials.h"
#include "Enums.h"

class Material
{
public:
	Material();
	Material(GLfloat aIntensity, GLfloat dIntensity, GLfloat sIntensity, int materialType, int* currTexture);

	void UseMaterial(GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation, GLuint specularIntensityLocation, GLuint shininessLocation,
		GLuint ambientColourLocation, GLuint diffuseColourLocation, GLuint specularColourLocation);
	void updateMaterial(GLfloat aIntensity, GLfloat dIntensity, GLfloat sIntensity);
	void setMaterial(int materialType, int* currentTexture);
	const char** getMaterials();
	void printMaterialInfo();

	void setBrass();
	void setBronze();
	void setPolishedBronze();
	void setChrome();
	void setCopper();
	void setPolishedCopper();
	void setGold();
	void setPolishedGold();
	void setPewter();
	void setSilver();
	void setPolishedSilver();
	void setEmerald();
	void setJade();
	void setObsidian();
	void setPearl();
	void setRuby();
	void setTurquoise();
	void setBlackPlastic();
	void setBlackRubber();
	void setPlain();

	~Material();

private:
	GLfloat ambientIntensity, diffuseIntensity, specularIntensity;
	glm::vec4 ambientColour, diffuseColour, specularColour;

	GLfloat shininess;
	const char* materialNames[19] = { "mosiadz", "braz", "polerowany braz", "chrom", "miedz", "polerowana miedz", "zloto", "polerowane zloto", "grafit", "srebro", "polerowane srebro", "szmaragd", "jadeit", "obsydian", "perla", "rubin", "turkus", "czarny plastik", "czarna guma" };
};

