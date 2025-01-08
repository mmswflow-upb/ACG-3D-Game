#include "Camera\camera.h"
#include "Resources/GameLoader.h" // Include the GameLoader header
#include "Game/Maps/Map.h"
#include "Game/Characters/Main Character/Main_Char.h"
#include "Game/Celestials/Celestial.h"

void processKeyboardInput(bool paused, bool spectateMode, Main_Char& mc);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Window window("Red Evil: The Laylasaurus Quest", 800, 800);
Camera camera;

glm::vec3 lightColor(1.0f, 0.8f, 0.2f);
glm::vec3 lightPos(0.0f, 100.0f, -200.0f);

int main()
{
	glClearColor(0.2f, 0.2f, .6f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Load the sun using GameLoader
	Mesh sunMesh = GameLoader::loadCelestialMesh(CelestialPack::Sun);
	Shader sunShader = GameLoader::loadCelestialShader(CelestialPack::Sun);

	//Load the map using GameLoader
	Mesh mapMesh = GameLoader::loadMapMesh(MapPack::Ver1);
	Shader mapShader = GameLoader::loadMapShader(MapPack::Ver1);

	Mesh mcMesh = GameLoader::loadCharacterMesh(CharacterPack::Main);
	Shader mcShader = GameLoader::loadCharacterShader(CharacterPack::Main);

	Celestial sun(sunMesh, sunShader, CelestialPack::Sun);

	Main_Char mc(mcMesh, mcShader, CharacterPack::Main);


	Map map(mapMesh, mapShader, MapPack::Ver1, mc);
	map.addCelestial(sun);
	
	camera.setCameraPosition(glm::vec3(0.0f,10.0f,0.0f));

	// Check if we close the window or press the escape button
	while ( 
		glfwWindowShouldClose(window.getWindow()) == 0)
	{
		//Handle user input
		window.handleEscapeToMenuInput();
		window.update();
		window.clear();

		//These are computed at the top (in main loop then shared with other classes)

		float time = glfwGetTime();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		bool paused = window.isPaused();
		bool spectateMode = window.isSpectating();
		bool animateLiquids = window.isAnimatingLiquids();

		processKeyboardInput(paused, spectateMode, mc);


		glm::mat4 ProjectionMatrix = glm::perspective(90.0f, window.getWidth() * 1.0f / window.getHeight(), 0.1f, 10000.0f);
		glm::mat4 ViewMatrix = glm::lookAt(camera.getCameraPosition(), camera.getCameraPosition() + camera.getCameraViewDirection(), camera.getCameraUp());

		//Update movement of projectiles

		//Check collisions of characters with projectiles
		//map.checkProjectileCollisions();

		//Mission checker will see if there's any dead character (2 ways of ending the game)


		//Movement of characters(except for MC) and celestials
		map.moveCelestials(deltaTime);

		//Check collisions of characters with (non-projectiles)
		map.checkObstacleCollisions();


		//Render the scene 
		//glm::vec3 lightPos, lightColor;
		//Celestial::determineTimeAndSetLight(sun, moon, lightColor, lightPos);
		map.render(ProjectionMatrix, ViewMatrix, lightColor, lightPos, camera, spectateMode, animateLiquids, time);
		


		// Render UI last
		window.renderGUI();
	}

	return 0;
}
void processKeyboardInput(bool paused, bool spectateMode, Main_Char& mc)
{
	float cameraSpeed = 30 * deltaTime;

	if (!paused) {
		// Translation
		if (window.isPressed(GLFW_KEY_W))
			camera.keyboardMoveFront(cameraSpeed, spectateMode);
		if (window.isPressed(GLFW_KEY_S))
			camera.keyboardMoveBack(cameraSpeed, spectateMode);
		if (window.isPressed(GLFW_KEY_A))
			camera.keyboardMoveLeft(cameraSpeed, spectateMode);
		if (window.isPressed(GLFW_KEY_D))
			camera.keyboardMoveRight(cameraSpeed, spectateMode);
		if (window.isPressed(GLFW_KEY_SPACE))
			camera.keyboardMoveUp(cameraSpeed, spectateMode);
		if (window.isPressed(GLFW_KEY_LEFT_SHIFT))
			camera.keyboardMoveDown(cameraSpeed, spectateMode);
		double mouseX, mouseY;
		window.getMousePos(mouseX, mouseY);
		camera.setCursorOrientation(mouseX, mouseY);
		if (!spectateMode) {
			// Get the forward direction of the camera
			glm::vec3 cameraForward = camera.getCameraViewDirection();

			// Calculate the angle of rotation around the Y-axis
			float rotationAngle = glm::atan(cameraForward.x, cameraForward.z);

			// Convert the angle to degrees if necessary (OpenGL uses degrees in some cases)

			// Set the rotation of the main character
			mc.setRotation(rotationAngle);
			glm::vec3 newPos = camera.getCameraPosition();
			newPos.y -= 1.0f;
			mc.setPosition(newPos);

		}


	}
}