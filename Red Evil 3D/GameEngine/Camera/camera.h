#pragma once

#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "..\Graphics\window.h"

const float camera_sensitivity = 0.1f;


class Camera
{
	private:
		glm::vec3 cameraPosition;
		glm::vec3 cameraViewDirection;
		glm::vec3 cameraUp;
		glm::vec3 cameraRight;

		float yaw = -90.0f;
		float pitch = 0.0f;
		double lastMouseX;
		double lastMouseY;
		bool firstMove = true;

	public:
		Camera();
		Camera(glm::vec3 cameraPosition);
		Camera(glm::vec3 cameraPosition, glm::vec3 cameraViewDirection, glm::vec3 cameraUp);
		~Camera();
		glm::vec3 getCameraPosition() const;
		glm::vec3 getCameraViewDirection() const;
		glm::vec3 getCameraUp() const;

		void keyboardMoveFront(float cameraSpeed, bool spectateMode);
		void keyboardMoveBack(float cameraSpeed, bool spectateMode);
		void keyboardMoveLeft(float cameraSpeed, bool );
		void keyboardMoveRight(float cameraSpeed, bool spectateMode);
		void keyboardMoveUp(float cameraSpeed, bool spectateMode);
		void keyboardMoveDown(float cameraSpeed, bool spectateMode);

		void setCursorOrientation(double x, double y);


		void setCameraPosition(glm::vec3);
};

