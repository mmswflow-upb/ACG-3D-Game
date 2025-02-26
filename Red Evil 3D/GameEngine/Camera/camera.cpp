#include "camera.h"
#include <iostream>
Camera::Camera(glm::vec3 cameraPosition)
{
	this->cameraPosition = cameraPosition;
	this->cameraViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
}

Camera::Camera()
{
	this->cameraPosition = glm::vec3(0.0f, 0.0f, 100.0f);
	this->cameraViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
}

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraViewDirection, glm::vec3 cameraUp)
{
	this->cameraPosition = cameraPosition;
	this->cameraViewDirection = cameraViewDirection;
	this->cameraUp = cameraUp;
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
}

Camera::~Camera()
{
}

void Camera::keyboardMoveFront(float cameraSpeed, bool *spectateMode)
{

	float originalY = cameraPosition.y; // Store the current y position
	cameraPosition += cameraViewDirection * cameraSpeed;
	if (spectateMode && *spectateMode == false) {
		cameraPosition.y = originalY; // Restore the original y position
	}
}

void Camera::keyboardMoveBack(float cameraSpeed, bool *spectateMode)
{

	float originalY = cameraPosition.y; // Store the current y position
	cameraPosition -= cameraViewDirection * cameraSpeed;
	if (spectateMode && *spectateMode == false) {
		cameraPosition.y = originalY; // Restore the original y position
	}
}

void Camera::keyboardMoveLeft(float cameraSpeed, bool *spectateMode)
{

	float originalY = cameraPosition.y; // Store the current y position
	cameraRight = glm::cross(cameraViewDirection, cameraUp);
	cameraPosition -= cameraRight * cameraSpeed;
	if (spectateMode && *spectateMode == false) {
		cameraPosition.y = originalY; // Restore the original y position
	}
}

void Camera::keyboardMoveRight(float cameraSpeed, bool *spectateMode)
{

	float originalY = cameraPosition.y; // Store the current y position
	cameraRight = glm::cross(cameraViewDirection, cameraUp);
	cameraPosition += cameraRight * cameraSpeed;
	if (spectateMode && *spectateMode == false) {
		cameraPosition.y = originalY; // Restore the original y position
	}
}

void Camera::keyboardMoveUp(float cameraSpeed, bool *spectateMode)
{

	if (spectateMode && *spectateMode == false) {
		return;
	}

	cameraPosition += cameraUp * cameraSpeed ;
}

void Camera::keyboardMoveDown(float cameraSpeed, bool *spectateMode)
{

	if (spectateMode && *spectateMode == false) {
		return;
	}
	cameraPosition -= cameraUp * cameraSpeed ;
}

void Camera::setCursorOrientation(double x, double y) {


	if (firstMove) {
		lastMouseX = x;
		lastMouseY = y;
		firstMove = false;
	}

	float xOffset = x - lastMouseX;
	float yOffset = lastMouseY - y;
	lastMouseX = x;
	lastMouseY = y;


	xOffset *= camera_sensitivity;
	yOffset *= camera_sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	cameraViewDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraViewDirection.y = sin(glm::radians(pitch));
	cameraViewDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));


}


void Camera::setCameraPosition(glm::vec3 newPos) {
	cameraPosition = newPos;
}

glm::vec3 Camera::getCameraPosition() const
{
	return cameraPosition;
}

glm::vec3 Camera::getCameraViewDirection() const
{
	return cameraViewDirection;
}

glm::vec3 Camera::getCameraUp() const
{
	return cameraUp;
}

