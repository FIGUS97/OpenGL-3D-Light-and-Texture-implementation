#pragma once

#include "stdio.h"
#include "Camera.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	Window();

	Window(GLint windowWidth, GLint windowHeight);

	int Initialise();

	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getLastX();
	GLfloat getLastY();
	bool getMovingMode();
	GLFWwindow* getMainWindow();

	static void setCameraPointer(Camera* cameraPointer);

	void swapBuffers() { glfwSwapBuffers(mainWindow); }


	~Window();

private:
	GLFWwindow* mainWindow;
	static Camera* camera;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
	static void handleMouseButtons(GLFWwindow* window, int button, int action, int mods);
};