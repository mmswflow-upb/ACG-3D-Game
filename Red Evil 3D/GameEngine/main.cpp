#include "Graphics\window.h"
#include "Camera\camera.h"
#include "Shaders\shader.h"
#include "Model Loading\mesh.h"
#include "Model Loading\texture.h"
#include "Model Loading\meshLoaderObj.h"
#include "Resources/GameLoader.h" // Include the GameLoader header

void processKeyboardInput(bool paused);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Window window("Red Evil: The Laylasaurus Quest", 800, 800);
Camera camera;

glm::vec3 lightColor = glm::vec3(1.0f);
glm::vec3 lightPos = glm::vec3(-180.0f, 100.0f, -200.0f);

int main()
{
	glClearColor(0.2f, 0.2f, .6f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Load the sun using GameLoader
	Mesh sun = GameLoader::loadCelestialMesh(CelestialPack::Sun);
	Shader sunShader = GameLoader::loadCelestialShader(CelestialPack::Sun);

	// Check if we close the window or press the escape button
	while ( 
		glfwWindowShouldClose(window.getWindow()) == 0)
	{
		window.handleEscapeToMenuInput();
		window.update();
		window.clear();

		float time = glfwGetTime();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processKeyboardInput(window.isPaused());

		//// Code for the light ////

		sunShader.use();

		glm::mat4 ProjectionMatrix = glm::perspective(90.0f, window.getWidth() * 1.0f / window.getHeight(), 0.1f, 10000.0f);
		glm::mat4 ViewMatrix = glm::lookAt(camera.getCameraPosition(), camera.getCameraPosition() + camera.getCameraViewDirection(), camera.getCameraUp());

		GLuint MatrixID = glGetUniformLocation(sunShader.getId(), "MVP");

		// Model transformation for the sun
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, lightPos);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Render the sun
		sun.draw(sunShader);

		//// End code for the light ////

		// Render UI last
		window.renderGUI();
	}

	return 0;
}

void processKeyboardInput(bool paused)
{
	float cameraSpeed = 30 * deltaTime;

	if (!paused) {
		// Translation
		if (window.isPressed(GLFW_KEY_W))
			camera.keyboardMoveFront(cameraSpeed);
		if (window.isPressed(GLFW_KEY_S))
			camera.keyboardMoveBack(cameraSpeed);
		if (window.isPressed(GLFW_KEY_A))
			camera.keyboardMoveLeft(cameraSpeed);
		if (window.isPressed(GLFW_KEY_D))
			camera.keyboardMoveRight(cameraSpeed);
		if (window.isPressed(GLFW_KEY_SPACE))
			camera.keyboardMoveUp(cameraSpeed);
		if (window.isPressed(GLFW_KEY_LEFT_SHIFT))
			camera.keyboardMoveDown(cameraSpeed);

		double mouseX, mouseY;
		window.getMousePos(mouseX, mouseY);
		camera.setCursorOrientation(mouseX, mouseY);
	}
}
