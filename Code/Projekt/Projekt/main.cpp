#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"
#include "ImGuiWindow.h"
#include "Enums.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

const float toRadians = 3.14159265f / 180.0f;
const float pi = 3.14159265f;

Window mainWindow;
Shader* shaderSmooth, * shaderFlat, * currentShader;
Mesh* sphereMesh, * cubeMesh, * pyramideMesh, * cylinderMesh;
Mesh* lightSphereMesh;
Camera camera;
ImGuiWindow imGuiWindow;


int currentModel = 0;
int currentTexture = 0;
int currShader = 0;
int currentMaterial;

Texture textures[20];

Material material;

DirectionalLight directionalLight;
PointLight pointLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

static const char* vShaderSmooth = "Shaders/shader.vert";
static const char* fShaderSmooth = "Shaders/fragShader.glsl";
static const char* vShaderFlat = "Shaders/shaderFLAT.vert";
static const char* fShaderFlat = "Shaders/fragShaderFLAT.glsl";

glm::vec3 calcDistinctNormal(glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3)
{
	float nx, ny, nz;

	// find 2 edge vectors: v1-v2, v1-v3
	glm::vec3 ev1(vert2.x - vert1.x, vert2.y - vert1.y, vert2.z - vert1.z);
	glm::vec3 ev2(vert3.x - vert1.x, vert3.y - vert1.y, vert3.z - vert1.z);

	// cross product: e1 x e2
	glm::vec3 normal = glm::cross(ev1, ev2);

	normal = glm::normalize(normal);

	return normal;
}

void calcCubicNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 normal = calcDistinctNormal(glm::vec3(vertices[in2], vertices[in2 + 1], vertices[in2 + 2]),
			glm::vec3(vertices[in1], vertices[in1 + 1], vertices[in1 + 2]),
			glm::vec3(vertices[in0], vertices[in0 + 1], vertices[in0 + 2]));

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}
}

Mesh* CreateCube()
{
	enum verts {
		A = 0,
		B = 1,
		C = 2,
		D = 3,
		E = 4,
		F = 5,
		G = 6,
		H = 7
	};
	unsigned int indices[] = {
		A, F, B,
		A, E, F,
		B, C, G,
		B, G, F,
		C, D, H,
		C, H, G,
		D, A, B,
		D, B, C,
		E, H, D,
		E, D, A,
		G, H, E,
		G, F, E
	};

	GLfloat vertices[] = {
		// x	y		z	tex: x		y	norm: x		y	 z
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, -1.0f,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,		4.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f,		3.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,		3.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,		4.0f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	//calcCubicNormals(indices, 36, vertices, 64, 8, 5);

	Mesh* cube;
	cube = new Mesh();
	cube->CreateMesh(vertices, indices, 64, 36);

	return cube;
}

Mesh* CreatePyramide()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, -0.6f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};
	calcCubicNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* pyramide;
	pyramide = new Mesh();
	pyramide->CreateMesh(vertices, indices, 32, 12);

	return pyramide;
}

Mesh* CreateCylinder(float baseRadius, float topRadius, float height, int sectorCount, int stackCount)
{
	float x, y, z;
	float s, t;
	float radius;

	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;
	unsigned int verticesCount = 0, indicesCount = 0;

	// generate Normals
	float sectorStep = 2 * pi / sectorCount;
	float sectorAngle;

	float zAngle = atan2(baseRadius - topRadius, height);
	float x0 = cos(zAngle);
	float y0 = 0;
	float z0 = sin(zAngle);

	std::vector<float> sideNormals;

	for (int i = 0; i <= sectorCount; ++i)
	{
		sectorAngle = i * sectorStep;
		sideNormals.push_back(cos(sectorAngle) * x0 - sin(sectorAngle) * y0);
		sideNormals.push_back(sin(sectorAngle) * x0 + cos(sectorAngle) * y0);
		sideNormals.push_back(z0);
	}

	// generate unit circle
	std::vector<float> unitCircleVertices;

	for (int i = 0; i <= sectorCount; ++i)
	{
		sectorAngle = i * sectorStep;
		unitCircleVertices.push_back(cos(sectorAngle));  // x
		unitCircleVertices.push_back(sin(sectorAngle));  // y
		unitCircleVertices.push_back(0);				 // z
	}

	// generate vertices
	for (int i = 0; i <= stackCount; ++i)
	{
		z = -(height * 0.5f) + (float)i / stackCount * height;      // vertex position z
		radius = baseRadius + (float)i / stackCount * (topRadius - baseRadius);     // lerp
		float t = 1.0f - (float)i / stackCount;   // top-to-bottom

		for (int j = 0, k = 0; j <= sectorCount; ++j, k += 3)
		{
			x = unitCircleVertices[k];
			y = unitCircleVertices[k + 1];

			// x y z
			vertices.push_back(x * radius);
			vertices.push_back(y * radius);
			vertices.push_back(z);

			// texel x y
			vertices.push_back((GLfloat)j / sectorCount);
			vertices.push_back(t);

			// normals x y z
			vertices.push_back(sideNormals[k]);
			vertices.push_back(sideNormals[k + 1]);
			vertices.push_back(sideNormals[k + 2]);
			verticesCount += 8;
		}
	}

	// remember where the base.top vertices start
	unsigned int baseVertexIndex = (unsigned int)vertices.size() / 3;

	// put vertices of base of cylinder
	z = -height * 0.5f;
	// x y z
	vertices.push_back(0);
	vertices.push_back(0);
	vertices.push_back(z);

	// texel x y
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);

	// normals x y z
	vertices.push_back(0);
	vertices.push_back(0);
	vertices.push_back(-1);
	verticesCount += 8;

	for (int i = 0, j = 0; i < sectorCount; ++i, j += 3)
	{
		x = unitCircleVertices[j];
		y = unitCircleVertices[j + 1];
		// x y z
		vertices.push_back(x * baseRadius);
		vertices.push_back(y * baseRadius);
		vertices.push_back(z);

		// texel x y
		vertices.push_back(-x * 0.5f + 0.5f);
		vertices.push_back(-y * 0.5f + 0.5f);    // flip horizontal

		// normals x y z
		vertices.push_back(0);
		vertices.push_back(0);
		vertices.push_back(-1);
		verticesCount += 8;
	}

	// remember where the base vertices start
	unsigned int topVertexIndex = (unsigned int)vertices.size() / 3;

	// put vertices of top of cylinder
	z = height * 0.5f;
	// x y z
	vertices.push_back(0);
	vertices.push_back(0);
	vertices.push_back(z);

	// texel x y
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);    // flip horizontal

	// normals x y z
	vertices.push_back(0);
	vertices.push_back(0);
	vertices.push_back(1);
	verticesCount += 8;
	for (int i = 0, j = 0; i < sectorCount; ++i, j += 3)
	{
		x = unitCircleVertices[j];
		y = unitCircleVertices[j + 1];

		// x y z
		vertices.push_back(x * topRadius);
		vertices.push_back(y * topRadius);
		vertices.push_back(z);

		// texel x y
		vertices.push_back(x * 0.5f + 0.5f);
		vertices.push_back(-y * 0.5f + 0.5f);    // flip horizontal

		// normals x y z
		vertices.push_back(0);
		vertices.push_back(0);
		vertices.push_back(1);
		verticesCount += 8;
	}

	// put indices for sides
	unsigned int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // bebinning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 trianles per sector
			indices.push_back(k1);
			indices.push_back(k1 + 1);
			indices.push_back(k2);

			indices.push_back(k2);
			indices.push_back(k1 + 1);
			indices.push_back(k2 + 1);
			indicesCount += 6;
		}
	}

	// remember where the base indices start
	int baseIndex = (unsigned int)indices.size();

	// put indices for base
	for (int i = 0, k = baseVertexIndex + 1; i < sectorCount; ++i, ++k)
	{
		if (i < (sectorCount - 1))
		{
			indices.push_back(baseVertexIndex);
			indices.push_back(k + 1);
			indices.push_back(k);
			indicesCount += 3;
		}
		else    // last triangle
		{
			indices.push_back(baseVertexIndex);
			indices.push_back(baseVertexIndex + 1);
			indices.push_back(k);
			indicesCount += 3;
		}
	}

	// remember where the base indices start
	int topIndex = (unsigned int)indices.size();

	for (int i = 0, k = topVertexIndex + 1; i < sectorCount; ++i, ++k)
	{
		if (i < (sectorCount - 1))
		{
			indices.push_back(topVertexIndex);
			indices.push_back(k);
			indices.push_back(k + 1);
			indicesCount += 3;
		}
		else
		{
			indices.push_back(topVertexIndex);
			indices.push_back(k);
			indices.push_back(topVertexIndex + 1);
			indicesCount += 3;
		}
	}

	Mesh* cylinder;
	cylinder = new Mesh();
	cylinder->CreateMesh(vertices.data(), indices.data(), verticesCount, indicesCount);

	return cylinder;

}

Mesh* CreateSphere(GLfloat radius, int sectorCount, int stackCount)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;
	float x, y, z, xy;
	float nx, ny, nz, lengthInv = 1.0f / radius;
	float s, t;
	int verticesCount = 0, indicesCount = 0;

	float sectorStep = 2 * pi / sectorCount;
	float stackStep = pi / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = pi / 2 - i * stackStep;
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);

		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;

			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// Texels coords
			s = (GLfloat)j / sectorCount;
			t = (GLfloat)i / stackCount;

			vertices.push_back(s);
			vertices.push_back(t);

			// Normals
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;

			vertices.push_back(nx);
			vertices.push_back(ny);
			vertices.push_back(nz);
			verticesCount += 8;
		}
	}


	// indices
	unsigned int k1, k2;

	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);
		k2 = k1 + sectorCount + 1;

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
				indicesCount += 3;
			}

			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
				indicesCount += 3;
			}
		}
	}

	Mesh* sphere;
	sphere = new Mesh();
	sphere->CreateMesh(vertices.data(), indices.data(), verticesCount, indicesCount);
	return sphere;
}

void CreateShaders()
{
	shaderSmooth = new Shader();
	shaderSmooth->CreateFromFiles(vShaderSmooth, fShaderSmooth);

	shaderFlat = new Shader();
	shaderFlat->CreateFromFiles(vShaderFlat, fShaderFlat);
}

void CreateModels()
{
	cubeMesh = CreateCube();
	cylinderMesh = CreateCylinder(4, 4, 6, 36, 18);
	pyramideMesh = CreatePyramide();
	sphereMesh = CreateSphere(4.0f, 36, 18);
	lightSphereMesh = CreateSphere(0.5f, 24, 12);
}

void CreateTextures() {
	textures[brass] = Texture(const_cast<char*>("Textures/png/brass.png"), GL_RGB, GL_RGB);
	textures[bronze] = Texture(const_cast<char*>("Textures/png/bronze.png"), GL_RGB, GL_RGB);
	textures[polishedBronze] = Texture(const_cast<char*>("Textures/png/polishedBronze.png"), GL_RGB, GL_RGB);
	textures[chrome] = Texture(const_cast<char*>("Textures/png/chrome.png"), GL_RGB, GL_RGB);
	textures[copper] = Texture(const_cast<char*>("Textures/png/copper.png"), GL_RGB, GL_RGB);
	textures[polishedCopper] = Texture(const_cast<char*>("Textures/png/polishedCopper.png"), GL_RGB, GL_RGB);
	textures[gold] = Texture(const_cast<char*>("Textures/png/gold.png"), GL_RGBA, GL_RGBA);
	textures[polishedGold] = Texture(const_cast<char*>("Textures/png/polishedGoldEH.png"), GL_RGB, GL_RGB);
	textures[pewter] = Texture(const_cast<char*>("Textures/png/pewterEH.png"), GL_RGB, GL_RGB);
	textures[silver] = Texture(const_cast<char*>("Textures/png/SilverRGB.png"), GL_RGBA, GL_RGBA);
	textures[polishedSilver] = Texture(const_cast<char*>("Textures/png/PolishedSilver.png"), GL_RGB, GL_RGB);
	textures[emerald] = Texture(const_cast<char*>("Textures/png/emeraldRGB.png"), GL_RGBA, GL_RGBA);
	textures[jade] = Texture(const_cast<char*>("Textures/png/JadeRGB.png"), GL_RGBA, GL_RGBA);
	textures[obsidian] = Texture(const_cast<char*>("Textures/png/obsidian.png"), GL_RGB, GL_RGB);
	textures[pearl] = Texture(const_cast<char*>("Textures/png/pearl.png"), GL_RGB, GL_RGB);
	textures[ruby] = Texture(const_cast<char*>("Textures/png/rubyRGB.png"), GL_RGBA, GL_RGBA);
	textures[turquoise] = Texture(const_cast<char*>("Textures/png/TurquoiseEH.png"), GL_RGB, GL_RGB);
	textures[blackPlastic] = Texture(const_cast<char*>("Textures/png/black.png"), GL_RGB, GL_RGB);
	textures[blackRubber] = Texture(const_cast<char*>("Textures/png/black.png"), GL_RGB, GL_RGB);
	textures[plain] = Texture(const_cast<char*>("Textures/png/pearl.png"), GL_RGB, GL_RGB);

	for (int i = 0; i < 20; i++)
		textures[i].LoadTexture();
}

void CreateLights() {
	directionalLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.05f, 0.5f, 0.6f,
		0.0f, 0.0f, -1.0f);

	pointLight = PointLight(0.0f, 0.0f, 1.0f,
		0.8f, 1.0f, 0.6f,
		0.0f, 0.0f, 5.0f,
		0.5f, 0.4f, 0.3f);
}

void updateSphere(int modelType, int sectorNumber, int stackNumber)
{
	sphereMesh = CreateSphere(4.0f, sectorNumber, stackNumber);
}

int main()
{
	std::cout << "Loading..." << std::endl;
	mainWindow = Window(1366, 768);
	mainWindow.Initialise();

	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

	CreateShaders();
	CreateModels();
	CreateTextures();
	CreateLights();

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(mainWindow.getMainWindow(), false, "#version 330");
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();
	imGuiWindow = ImGuiWindow(&currentModel, &currentTexture, &currShader);

	camera = Camera(glm::vec3(13.0f, 5.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, -40.0f, 5.0f, 0.5f, 1);
	mainWindow.setCameraPointer(&camera);

	float materialAmbientIntensity = 1.0, materialDiffuseIntensity = 1.0f, materialSpecularIntensity = 1.0f;
	material = Material(1.0f, 1.0f, 1.0f, brass, &currentTexture);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformMaterialSpecularIntensity = 0, uniformMaterialShininess = 0, uniformMaterialAmbientIntensity = 0, uniformMaterialDiffuseIntensity = 0,
		uniformMaterialSpecularColour = 0, uniformMaterialDiffuseColour = 0, uniformMaterialAmbientColour = 0;

	int i = 0;
	ImVec4 directionalColour = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	ImVec4 pointColour = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	float scaleFactor = 1.0f, scaleFactorX = 1.0f, scaleFactorY = 1.0f, scaleFactorZ = 1.0f;
	bool xRotation = true, yRotation = false, zRotation = false;
	float rotationFactor = 0.0f;
	float directionalAmbientFactor = 0.1f, directionalDiffuseFactor = 0.5f, directionalSpecularFactor = 0.8f;
	float pointAmbientFactor = 0.3f, pointDiffuseFactor = 0.7f, pointSpecularFactor = 0.7f,
		pointConstantFactor = 1.0f, pointLinearFactor = 0.0f, pointExponentFactor = 0.0f;
	float pointLightIntensity = 0.5f;
	float pointLightSpeed = 0.8f;
	int sphereSectorCount = 36, sphereStackCount = 18;
	bool isTextureOn = true, areLinesOn = false;
	bool pointAmbientTurnedOn = true, pointDiffuseTurnedOn = true, pointSpecularTurnedOn = true;
	bool directionalAmbientTurnedOn = true, directionalDiffuseTurnedOn = false, directionalSpecularTurnedOn = false;
	glm::vec3 pointLightPosition(0.0f, 0.0f, 0.0f);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	std::cout << "Loaded." << std::endl;

	while (!mainWindow.getShouldClose())
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (currShader == 0)
		{
			currentShader = shaderSmooth;
		}
		else {
			currentShader = shaderFlat;
		}

		glm::mat4 mainModel(1.0f);
		glm::mat4 pointLightPosModel(1.0f);
		io.MousePos = ImVec2(mainWindow.getLastX(), mainWindow.getLastY());

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		ImGui_ImplGlfwGL3_NewFrame();
		imGuiWindow.displayModelChooseWindow(&isTextureOn, &areLinesOn, &currShader);
		imGuiWindow.displayTransformationWindow(&scaleFactor, &scaleFactorX, &scaleFactorY, &scaleFactorZ, &xRotation, &yRotation, &zRotation, &rotationFactor);
		imGuiWindow.displayDirectionalLightWindow(&directionalColour, &directionalAmbientFactor, &directionalDiffuseFactor, &directionalSpecularFactor, &directionalAmbientTurnedOn, &directionalDiffuseTurnedOn, &directionalSpecularTurnedOn);
		imGuiWindow.displayPointLightWindow(&pointColour, &pointLightIntensity, &pointAmbientFactor, &pointDiffuseFactor, &pointSpecularFactor, &pointExponentFactor, &pointLinearFactor, &pointConstantFactor, &pointLightSpeed, &pointAmbientTurnedOn, &pointDiffuseTurnedOn, &pointSpecularTurnedOn);
		imGuiWindow.displayNavigationWindow();
		if (currentModel == Sphere || currentModel == AngularSphere)
		{
			imGuiWindow.displaySphereSetupWindow(&sphereSectorCount, &sphereStackCount);
		}
		imGuiWindow.displayMaterialWindow(&currentMaterial, material.getMaterials(), 19);

		if (imGuiWindow.isSphereChanged())
		{
			updateSphere(currentModel, sphereSectorCount, sphereStackCount);
			imGuiWindow.sphereChangeEnded();
		}

		material.setMaterial(currentMaterial, &currentTexture);
		material.updateMaterial(materialAmbientIntensity, materialDiffuseIntensity, materialSpecularIntensity);

		pointLight.updateLoopPointLightPos(pointLightSpeed);
		pointLight.updateAmbientIntensity(pointAmbientTurnedOn ? pointAmbientFactor : 0.0f);
		pointLight.updateDiffuseIntensity(pointDiffuseTurnedOn ? pointDiffuseFactor : 0.0f);
		pointLight.updateSpecularIntensity(pointSpecularTurnedOn ? pointSpecularFactor : 0.0f);
		pointLight.updateColour(glm::vec3(pointColour.x, pointColour.y, pointColour.z));
		pointLight.updatePointLightFactors(pointExponentFactor, pointLinearFactor, pointConstantFactor);
		pointLightPosition = pointLight.getPointLightPos();

		directionalLight.updateAmbientIntensity(directionalAmbientTurnedOn ? directionalAmbientFactor : 0.0f);
		directionalLight.updateDiffuseIntensity(directionalDiffuseTurnedOn ? directionalDiffuseFactor : 0.0f);
		directionalLight.updateSpecularIntensity(directionalSpecularTurnedOn ? directionalSpecularFactor : 0.0f);
		directionalLight.updateColour(glm::vec3(directionalColour.x, directionalColour.y, directionalColour.z));

		camera.keyControl(mainWindow.getKeys(), deltaTime);

		currentShader->UseShader();
		uniformModel = currentShader->GetModelLocation();
		uniformProjection = currentShader->GetProjectionLocation();
		uniformView = currentShader->GetViewLocation();
		uniformEyePosition = currentShader->GetEyePositionLocation();

		uniformMaterialAmbientIntensity = currentShader->GetMaterialAmbientIntensityLocation();
		uniformMaterialDiffuseIntensity = currentShader->GetMaterialDiffuseIntensityLocation();
		uniformMaterialSpecularIntensity = currentShader->GetMaterialSpecularIntensityLocation();
		uniformMaterialAmbientColour = currentShader->GetMaterialAmbientColourLocation();
		uniformMaterialDiffuseColour = currentShader->GetMaterialDiffuseColourLocation();
		uniformMaterialSpecularColour = currentShader->GetMaterialSpecularColourLocation();
		uniformMaterialShininess = currentShader->GetMaterialShininessLocation();

		currentShader->SetDirectionalLight(&directionalLight);
		currentShader->SetPointLight(&pointLight);

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		mainModel = glm::scale(mainModel, glm::vec3(scaleFactorX, scaleFactorY, scaleFactorZ));
		if (i % 2 == 0)
		{
			_sleep(10);
			if (camera.getCameraMode() == flyingMode)
			{
				camera.mouseControlFlyingMode(mainWindow.getXChange(), mainWindow.getYChange());
			}
			else {
				//std::cout << "stable mode" << std::endl;
				mainModel = glm::rotate(mainModel, rotationFactor * toRadians, glm::vec3((GLfloat)xRotation, (GLfloat)yRotation, (GLfloat)zRotation));
				camera.mouseControlStableMode(mainWindow.getKeys(), mainWindow.getLastX(), mainWindow.getLastY(), mainWindow.getXChange() + mainWindow.getLastX(), mainWindow.getLastY() - mainWindow.getYChange(), mainWindow.getBufferWidth(), mainWindow.getBufferHeight(), io.WantCaptureMouse);
			}
		}

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(mainModel));

		if (isTextureOn)
			textures[currentTexture].UseTexture();

		if (areLinesOn)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		material.UseMaterial(uniformMaterialAmbientIntensity, uniformMaterialDiffuseIntensity, uniformMaterialSpecularIntensity, uniformMaterialShininess,
			uniformMaterialAmbientColour, uniformMaterialDiffuseColour, uniformMaterialSpecularColour);

		switch (currentModel)
		{
		case Sphere:
			sphereMesh->RenderMesh();
			break;
		case Cube:
			cubeMesh->RenderMesh();
			break;
		case Cylinder:
			cylinderMesh->RenderMesh();
			break;
		case Pyramide:
			pyramideMesh->RenderMesh();
			break;
		}


		pointLight.updateAmbientIntensity(1.0f);
		currentShader->SetPointLight(&pointLight);
		pointLightPosModel = glm::translate(pointLightPosModel, pointLightPosition);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(pointLightPosModel));
		textures[plain].UseTexture();
		material.setMaterial(plain, &currentTexture);
		material.UseMaterial(uniformMaterialAmbientIntensity, uniformMaterialDiffuseIntensity, uniformMaterialSpecularIntensity, uniformMaterialShininess, uniformMaterialAmbientColour, uniformMaterialDiffuseColour, uniformMaterialSpecularColour);
		lightSphereMesh->RenderMesh();

		glUseProgram(0);

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		mainWindow.swapBuffers();
	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

