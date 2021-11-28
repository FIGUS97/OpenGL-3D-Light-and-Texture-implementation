#include "ImGuiWindow.h"

ImGuiWindow::ImGuiWindow()
{
	currentModel = 0;
	currentTexture = 0;
	currentShader = 0;
}

ImGuiWindow::ImGuiWindow(int* currModel, int* currTexture, int* currShader)
{
	currentModel = currModel;
	currentTexture = currTexture;
	currentShader = currShader;
}


void ImGuiWindow::displayModelChooseWindow(bool* isTextureOn, bool* areLinesOn, int* currShader) {

	ImGui::SetNextWindowPos(ImVec2(1, 4));
	ImGui::SetNextWindowSize(ImVec2(307, 213));
	ImGui::Begin("Wybor modelu");
	if (ImGui::Button("Sfera"))
		*currentModel = Sphere;
	ImGui::SameLine();
	if (ImGui::Button("Prostopadloscian"))
		*currentModel = Cube;
	ImGui::SameLine();
	if (ImGui::Button("Ostroslup"))
		*currentModel = Pyramide;
	ImGui::SameLine();
	if (ImGui::Button("Walec"))
		*currentModel = Cylinder;

	ImGui::Text("\n");
	ImGui::Checkbox("Tekstura", isTextureOn);
	ImGui::SameLine();
	ImGui::Checkbox("Siatka wielokatow", areLinesOn);

	ImGui::Text("\nWektory normalne:");
	ImGui::PushID(16);
	if (ImGui::SmallButton("Usrednione"))
		*currShader = smooth;
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(17);
	if (ImGui::SmallButton("Rownolegle"))
	{
		*currentShader = flat;
	}
	ImGui::PopID();

	ImGui::End();

}

void ImGuiWindow::displaySphereSetupWindow(int* sectorCount, int* stackCount)
{
	ImGui::SetNextWindowPos(ImVec2(2, 541));
	ImGui::SetNextWindowSize(ImVec2(304, 225));
	ImGui::Begin("Ustawienia Sfery");
	ImGui::Text("Ilosc wierzcholkow sfery:");
	ImGui::Text("Poziomo:");
	ImGui::Text("%d", *sectorCount);
	ImGui::SameLine();
	ImGui::PushID(12);
	if (ImGui::SmallButton("+")) {
		*sectorCount += 1;
		sphereChanged = true;
	}
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(13);
	if (ImGui::SmallButton("-")) {
		if (*sectorCount != 0) {
			*sectorCount -= 1;
			sphereChanged = true;
		}
	}
	ImGui::PopID();

	ImGui::Text("\nPionowo:");
	ImGui::Text("%i", *stackCount);
	ImGui::SameLine();
	ImGui::PushID(14);
	if (ImGui::SmallButton("+")) {
		*stackCount += 1;
		sphereChanged = true;
	}
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(15);
	if (ImGui::SmallButton("-"))
	{
		if (*stackCount != 0) {
			*stackCount -= 1;
			sphereChanged = true;
		}
	}
	ImGui::PopID();



	ImGui::End();
}

void ImGuiWindow::displayTransformationWindow(float* scaleFactor, float* scaleFactorX, float* scaleFactorY, float* scaleFactorZ, bool* xRotation, bool* yRotation, bool* zRotation, float* rotationFactor) {

	ImGui::SetNextWindowPos(ImVec2(1, 324));
	ImGui::SetNextWindowSize(ImVec2(306, 215));
	ImGui::Begin("Transformacje Modelu");

	ImGui::Text("Skaluj model:");
	ImGui::Text("Skala ogolna:");
	ImGui::SameLine();
	if (ImGui::SliderFloat("", scaleFactor, 0.0f, 1.5f))
	{
		*scaleFactorX = *scaleFactor;
		*scaleFactorY = *scaleFactor;
		*scaleFactorZ = *scaleFactor;
	}

	ImGui::Text("Skala X:     ");
	ImGui::SameLine();
	ImGui::SliderFloat(" ", scaleFactorX, 0.0f, 1.5f);

	ImGui::Text("Skala Y:     ");
	ImGui::SameLine();
	ImGui::SliderFloat("  ", scaleFactorY, 0.0f, 1.5f);

	ImGui::Text("Skala Z:     ");
	ImGui::SameLine();
	ImGui::SliderFloat("   ", scaleFactorZ, 0.0f, 1.5f);

	ImGui::Text("\nObroc model:");
	if (ImGui::RadioButton("X", *xRotation))
	{
		*xRotation = true;
		*yRotation = false;
		*zRotation = false;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Y", *yRotation))
	{
		*xRotation = false;
		*yRotation = true;
		*zRotation = false;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Z", *zRotation))
	{
		*xRotation = false;
		*yRotation = false;
		*zRotation = true;
	}
	ImGui::SliderFloat("    ", rotationFactor, 0.0f, 360.0f);

	ImGui::End();

}

void ImGuiWindow::displayDirectionalLightWindow(ImVec4* directionalColour, float* directionalAmbientFactor, float* directionalDiffuseFactor, float* directionalSpecularFactor, bool* ambientOn, bool* diffuseOn, bool* specularOn) {
	float zero = 0.0f;

	ImGui::SetNextWindowPos(ImVec2(1278, 607));
	ImGui::SetNextWindowSize(ImVec2(286, 157));
	ImGui::Begin("Ustawienia Swiatla Kierunkowego");

	ImGui::Text("Wspolczynnik Ambient");
	ImGui::PushID(28);
	ImGui::Checkbox("", ambientOn);
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(22);
	ImGui::SliderFloat("", (ambientOn ? directionalAmbientFactor : &zero), 0.0f, 1.0f);
	ImGui::PopID();

	ImGui::Text("Wspolczynnik Diffuse");
	ImGui::PushID(29);
	ImGui::Checkbox("", diffuseOn);
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(23);
	ImGui::SliderFloat("", (diffuseOn ? directionalDiffuseFactor : &zero), 0.0f, 1.0f);
	ImGui::PopID();

	ImGui::Text("Wspolczynnik Specular");
	ImGui::PushID(30);
	ImGui::Checkbox("", specularOn);
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(24);
	ImGui::SliderFloat("", (specularOn ? directionalSpecularFactor : &zero), 0.0f, 1.0f);
	ImGui::PopID();

	ImGui::End();

}

void ImGuiWindow::displayPointLightWindow(ImVec4* pointColour, float* overallIntensity, float* pointAmbientFactor, float* pointDiffuseFactor, float* pointSpecularFactor, float* pointQuadraticFactor, float* pointLinearFactor, float* pointConstantFactor, float* pointLightSpeed, bool* ambientOn, bool* diffuseOn, bool* specularOn) {
	float zero = 0.0f;
	bool lightOn = true;

	ImGui::SetNextWindowPos(ImVec2(1279, 178));
	ImGui::SetNextWindowSize(ImVec2(284, 427));
	ImGui::Begin("Ustawienia Swiatla Pozycyjnego");


	ImGui::Text("Kolor:");
	ImGui::PushID(1);
	ImGui::ColorEdit3(" ", (float*)pointColour);
	ImGui::PopID();

	ImGui::Text("\nIntensywnosc swiatla");
	ImGui::PushID(31);
	ImGui::Checkbox("", &lightOn);
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(32);
	if (ImGui::SliderFloat(" ", ((lightOn) ? overallIntensity : &zero), 0.0f, 1.0f))
	{
		*pointAmbientFactor = *overallIntensity;
		*pointDiffuseFactor = *overallIntensity;
		*pointSpecularFactor = *overallIntensity;
	}
	ImGui::PopID();

	ImGui::Text("\nWspolczynnik Ambient");
	ImGui::PushID(25);
	ImGui::Checkbox("", ambientOn);
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(2);
	ImGui::SliderFloat(" ", ((*ambientOn) ? pointAmbientFactor : &zero), 0.0f, 1.0f);
	ImGui::PopID();

	ImGui::Text("Wspolczynnik Diffuse");
	ImGui::PushID(26);
	ImGui::Checkbox("", diffuseOn);
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(3);
	ImGui::SliderFloat(" ", ((*diffuseOn) ? pointDiffuseFactor : &zero), 0.0f, 1.0f);
	ImGui::PopID();

	ImGui::Text("Wspolczynnik Specular");
	ImGui::PushID(27);
	ImGui::Checkbox("", specularOn);
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(4);
	ImGui::SliderFloat(" ", ((*specularOn) ? pointSpecularFactor : &zero), 0.0f, 1.0f);
	ImGui::PopID();

	ImGui::Text("\nWspolczynnik kwadratowy");
	ImGui::Text("%f", *pointQuadraticFactor);
	ImGui::SameLine();
	ImGui::PushID(21);
	if (ImGui::SmallButton("+"))
		*pointQuadraticFactor += 0.10f;
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(5);
	if (ImGui::SmallButton("-") && *pointQuadraticFactor != 0.0)
		*pointQuadraticFactor -= 0.10f;
	ImGui::PopID();


	ImGui::Text("Wspolczynnik liniowy");
	ImGui::Text("%f", *pointLinearFactor);
	ImGui::SameLine();
	ImGui::PushID(6);
	if (ImGui::SmallButton("+"))
		*pointLinearFactor += 0.10f;
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(7);
	if (ImGui::SmallButton("-") && *pointLinearFactor != 0.0)
		*pointLinearFactor -= 0.10f;
	ImGui::PopID();


	ImGui::Text("Wspolczynnik staly");
	ImGui::Text("%f", *pointConstantFactor);
	ImGui::SameLine();
	ImGui::PushID(8);
	if (ImGui::SmallButton("+"))
		*pointConstantFactor += 0.10f;
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(9);
	if (ImGui::SmallButton("-") && *pointConstantFactor != 0.0)
		*pointConstantFactor -= 0.10f;
	ImGui::PopID();

	ImGui::Text("\nPredkosc swiatla pozycyjnego");
	ImGui::Text("%f", *pointLightSpeed);
	ImGui::SameLine();
	ImGui::PushID(10);
	if (ImGui::SmallButton("+"))
		*pointLightSpeed += 0.10f;
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::PushID(11);
	if (ImGui::SmallButton("-") && *pointLightSpeed != 0.0)
		*pointLightSpeed -= 0.10f;
	ImGui::PopID();

	ImGui::End();

}

void ImGuiWindow::displayNavigationWindow() {
	ImGui::SetNextWindowPos(ImVec2(1279, 1));
	ImGui::SetNextWindowSize(ImVec2(286, 176));
	ImGui::Begin("Nawigacja");

	ImGui::Text("Dostepne tryby: Latanie i Obracanie");
	ImGui::Text("Klawisz M - zmiana trybu \n");
	ImGui::Text("Tryb Latania:");
	ImGui::Text("WSAD - poruszanie sie");
	ImGui::Text("Poruszanie mysza - obrot kamery \n");

	ImGui::Text("Tryb obracania:");
	ImGui::Text("Nacisniecie myszy i poruszenie \npowoduje obrot kamery");

	ImGui::End();
}

void ImGuiWindow::displayMaterialWindow(int* currMaterial, const char* materialNames[], int materialNamesCount)
{
	ImGui::SetNextWindowPos(ImVec2(1, 218));
	ImGui::SetNextWindowSize(ImVec2(307, 105));
	ImGui::Begin("Ustawienia Materialu");

	ImGui::Text("Material:");
	if (ImGui::BeginCombo("", materialNames[*currMaterial]))
	{
		for (int n = 0; n < materialNamesCount; n++)
		{
			bool selected = (materialNames[*currMaterial] == materialNames[n]);
			if (ImGui::Selectable(materialNames[n], selected))
				*currMaterial = n;
			if (selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	ImGui::End();
}

bool ImGuiWindow::isSphereChanged()
{
	return sphereChanged;
}

void ImGuiWindow::sphereChangeEnded()
{
	sphereChanged = false;
}

