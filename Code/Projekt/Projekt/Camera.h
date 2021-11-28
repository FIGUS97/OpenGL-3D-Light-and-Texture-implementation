#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>

#include "Enums.h"

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed, bool cameraMode);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControlFlyingMode(GLfloat xChange, GLfloat yChange);
	void mouseControlStableMode(bool* keys, GLfloat xLastMousePos, GLfloat yLastMousePos, GLfloat xPos, GLfloat yPos, GLfloat windowWidth, GLfloat windowHeight, bool isMouseOnWindow);
	bool changeMouseMode(bool* keys, GLFWwindow* mainWindow);



	void setCameraMode(bool camMode);
	bool getCameraMode();

	glm::vec3 getCameraPosition();

	glm::mat4 calculateViewMatrix();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	glm::vec3 center;

	bool cameraMode;
	bool firstStableMovePassed;


	GLfloat yaw;
	GLfloat pitch;

	GLfloat ylastRotateY, ylastRotateX, ylastRotateZ;
	GLfloat xlastRotateY, xlastRotateX, xlastRotateZ;

	GLfloat moveSpeed;
	GLfloat turnSpeed;
	GLfloat rotateSpeed;

	void update();
};

