#pragma once

#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <GLFW\glfw3.h>

#include "Enums.h"

class ImGuiWindow
{
public:
	ImGuiWindow();
	ImGuiWindow(int* currModel, int* currTexture, int* currShader);

	void displayModelChooseWindow(bool* isTextureOn, bool* areLinesOn, int* currShader);
	void displaySphereSetupWindow(int* sectorCount, int* stackCount);
	void displayTransformationWindow(float* scaleFactor, float* scaleFactorX, float* scaleFactorY, float* scaleFactorZ, bool* xRotation, bool* yRotation, bool* zRotation, float* rotationFactor);
	void displayDirectionalLightWindow(ImVec4* directionalColour, float* directionalAmbientFactor, float* directionalDiffuseFactor, float* directionalSpecularFactor, bool* ambientOn, bool* diffuseOn, bool* specularOn);
	void displayPointLightWindow(ImVec4* pointColour, float* overallIntensity, float* pointAmbientFactor, float* pointDiffuseFactor, float* pointSpecularFactor, float* pointQuadraticFactor, float* pointLinearFactor, float* pointConstantFactor, float* pointLightSpeed, bool* ambientOff, bool* diffuseOff, bool* specularOff);
	void displayNavigationWindow();
	void displayMaterialWindow(int* currMaterial, const char* materialNames[], int materialNamesCount);

	bool isSphereChanged();
	void sphereChangeEnded();

private:
	int* currentModel;
	int* currentTexture;
	int* currentShader;
	bool sphereChanged = false;
};

