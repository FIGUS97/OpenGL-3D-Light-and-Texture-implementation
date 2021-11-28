#include "Camera.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed, bool cameraMode)
{
	cameraMode = flyingMode;

	ylastRotateX = 1.0f;
	ylastRotateY = 0.0f;
	ylastRotateZ = 0.0f;

	xlastRotateX = 0.0f;
	xlastRotateY = 1.0f;
	xlastRotateZ = 0.0f;

	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	center = glm::vec3(0.0f, 0.0f, 0.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;
	setCameraMode(stableMode);

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat movement = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * movement;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * movement;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * movement;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * movement;
	}
}

bool Camera::changeMouseMode(bool* keys, GLFWwindow* mainWindow)
{
	if (cameraMode)
	{ // stable
		glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else { //flying
		glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	return cameraMode;
}

void Camera::setCameraMode(bool camMode)
{
	cameraMode = camMode;
}

bool Camera::getCameraMode()
{
	return cameraMode;
}

void Camera::mouseControlFlyingMode(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

void Camera::mouseControlStableMode(bool* keys, GLfloat xLastMousePos, GLfloat yLastMousePos, GLfloat xPos, GLfloat yPos, GLfloat windowWidth, GLfloat windowHeight, bool isMouseOnWindow)
{
	if (keys[GLFW_MOUSE_BUTTON_LEFT] && !isMouseOnWindow) // przycisk jest klikniêty
	{
		glm::vec4 stableCameraPosition(position, 1);
		glm::vec4 modelCenterPoint(center, 1);

		GLfloat deltaAngleX = (2 * 3.14 / windowWidth);
		GLfloat deltaAngleY = (3.14 / windowHeight);

		GLfloat xAngle = (xLastMousePos - xPos) * deltaAngleX;
		GLfloat yAngle = (yLastMousePos - yPos) * deltaAngleY;

		if (position.x < 0)
			yAngle = -yAngle;

		float cosAngle = glm::dot(front, up);
		if (cosAngle * glm::abs(deltaAngleY) > 0.99f)
			deltaAngleY = 0;

		glm::mat4 rotationMatrixX(1.0f);
		rotationMatrixX = glm::rotate(rotationMatrixX, xAngle, up);
		stableCameraPosition = (rotationMatrixX * (stableCameraPosition - modelCenterPoint)) + modelCenterPoint;

		glm::mat4 rotationMatrixY(1.0f);
		rotationMatrixY = glm::rotate(rotationMatrixY, yAngle, right);
		glm::vec3 finalPosition = (rotationMatrixY * (stableCameraPosition - modelCenterPoint)) + modelCenterPoint;

		position = finalPosition;
		update();
	}
}

glm::mat4 Camera::calculateViewMatrix()
{
	if (cameraMode == flyingMode)
	{
		return glm::lookAt(position, position + front, up);
	}
	else {
		return glm::lookAt(position, center, up);
	}
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}
