#include "Camera\camera.h"
#include "Resources/GameLoader.h" // Include the GameLoader header
#include "Game/Maps/Map.h"
#include "Game/Characters/Main Character/Main_Char.h"
#include "Game/Celestials/Celestial.h"
#include "Graphics/window.h"
#include "Game/Trackers/GameTracker.h"


using namespace std;


float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int width = 800, height = 800;

bool* spectateMode = new bool(false);
bool* animating = new bool(true);
bool* paused = new bool(false);


pair<string, string> taskTitleAndDescription = { "Unkown Task", "Description Unavailable" };
map<string, string> inventoryItemsAndAmounts = { {"",""} };
pair<string, string> heldItemNameAndAmount = { "No Tool Equipped", "" };
Inventory* inv;


Window window("Red Evil: The Laylasaurus Quest", &width, &height, spectateMode, animating, paused, taskTitleAndDescription, inventoryItemsAndAmounts, heldItemNameAndAmount, nullptr, nullptr, nullptr);

void processKeyboardInput(Camera& camera, Main_Char& mc, Friend& friendCharacter, GameTracker& gameTracker, Map& currentMap, float deltaTime);

int main()
{
	glClearColor(0.2f, 0.2f, .6f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Camera camera(glm::vec3(0.0f, 20.5f, 0.0f));


	//Load projectiles 
	Mesh bulletMesh = GameLoader::loadProjectileMesh(ProjectileType::Bullet);
	Shader bulletShader = GameLoader::loadProjectileShader(ProjectileType::Bullet);
	Projectile bullet(bulletMesh, bulletShader, ProjectileType::Bullet, glm::vec3(1.0f,1.0f,1.0f), glm::vec3(1.0f, 1.0f, 1.0f));



	Mesh iceballMesh = GameLoader::loadProjectileMesh(ProjectileType::Iceball);
	Shader iceballShader = GameLoader::loadProjectileShader(ProjectileType::Iceball);
	Projectile iceball(iceballMesh, iceballShader, ProjectileType::Iceball, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));


	Mesh fireballMesh = GameLoader::loadProjectileMesh(ProjectileType::Fireball);
	Shader fireballShader = GameLoader::loadProjectileShader(ProjectileType::Fireball);
	Projectile fireball(fireballMesh, fireballShader, ProjectileType::Fireball, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	Mesh laylasaurusFireballMesh = GameLoader::loadProjectileMesh(ProjectileType::Fireball);
	Shader laylasaurusFireballShader = GameLoader::loadProjectileShader(ProjectileType::Fireball);
	Projectile laylasaurusFireball(laylasaurusFireballMesh, laylasaurusFireballShader, ProjectileType::LaylasaurusFireball, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));



	//Load Tools & Drops
	Mesh pistolMesh = GameLoader::loadGunMesh(GunPack::Pistol);
	Shader pistolShader = GameLoader::loadGunShader(GunPack::Pistol);
	Gun pistol(pistolMesh, pistolShader, GunPack::Pistol, bullet);

	Mesh ammo30Mesh = GameLoader::loadDropMesh(DropType::Ammo_30);
	Shader ammo30Shader = GameLoader::loadDropShader(DropType::Ammo_30);
	Drop ammo30(ammo30Mesh, ammo30Shader, DropType::Ammo_30);

	Mesh ammo60Mesh = GameLoader::loadDropMesh(DropType::Ammo_60);
	Shader ammo60Shader = GameLoader::loadDropShader(DropType::Ammo_60);
	Drop ammo60(ammo60Mesh, ammo60Shader, DropType::Ammo_60);

	Mesh medkitMesh = GameLoader::loadDropMesh(DropType::HealthPack);
	Shader medkitShader = GameLoader::loadDropShader(DropType::HealthPack);
	Drop medkit(medkitMesh, medkitShader, DropType::HealthPack);




	//Load Characters
	Mesh mcMesh = GameLoader::loadCharacterMesh(CharacterPack::Main);
	Shader mcShader = GameLoader::loadCharacterShader(CharacterPack::Main);
	Main_Char mainCharacter(mcMesh, mcShader, CharacterPack::Main);

	Mesh friendMesh = GameLoader::loadCharacterMesh(CharacterPack::Friend);
	Shader friendShader = GameLoader::loadCharacterShader(CharacterPack::Friend);
	Friend friendCharacter(friendMesh, friendShader, CharacterPack::Friend, laylasaurusFireball);

	window.setPointers(&mainCharacter, &friendCharacter, & camera);

	Mesh iceDynoMesh = GameLoader::loadCharacterMesh(CharacterPack::Ice_Dyno);
	Shader iceDynoShader = GameLoader::loadCharacterShader(CharacterPack::Ice_Dyno);
	Enemy iceDyno(iceDynoMesh, iceDynoShader, CharacterPack::Ice_Dyno, iceball);

	Mesh fireDynoMesh = GameLoader::loadCharacterMesh(CharacterPack::Fire_Dyno);
	Shader fireDynoShader = GameLoader::loadCharacterShader(CharacterPack::Fire_Dyno);
	Enemy fireDyno(fireDynoMesh, fireDynoShader, CharacterPack::Fire_Dyno, fireball);

	Mesh normalTreeMesh = GameLoader::loadAnimatableMesh(AnimatableType::NormalTree);
	Shader normalTreeShader = GameLoader::loadAnimatableShader(AnimatableType::NormalTree);
	Animatable normalTree(normalTreeMesh, normalTreeShader, AnimatableType::NormalTree);

	Mesh burntTreeMesh = GameLoader::loadAnimatableMesh(AnimatableType::BurntTree);
	Shader burntTreeShader = GameLoader::loadAnimatableShader(AnimatableType::BurntTree);
	Animatable burntTree(burntTreeMesh, burntTreeShader, AnimatableType::BurntTree);

	Mesh seaWaterMesh = GameLoader::loadAnimatableMesh(AnimatableType::SeaWater);
	Shader seaWaterShader = GameLoader::loadAnimatableShader(AnimatableType::SeaWater);
	Animatable seaWater(seaWaterMesh, seaWaterShader, AnimatableType::SeaWater);


	// Load the Celestials
	Mesh sunMesh = GameLoader::loadCelestialMesh(CelestialPack::Sun);
	Shader sunShader = GameLoader::loadCelestialShader(CelestialPack::Sun);
	Celestial sun(sunMesh, sunShader, CelestialPack::Sun);


	Mesh moonMesh = sunMesh;
	Shader moonShader = GameLoader::loadCelestialShader(CelestialPack::Moon);
	Celestial moon(moonMesh, moonShader, CelestialPack::Moon);


	//Load the map using GameLoader
	Mesh fullMapMesh = GameLoader::loadMapMesh(MapPack::FullNoTrees);
	Shader fullMapShader = GameLoader::loadMapShader(MapPack::FullNoTrees);
	Map currentMap(fullMapMesh, fullMapShader, MapPack::FullNoTrees, &mainCharacter, &friendCharacter,&sun, &moon, &camera, animating, paused, spectateMode);

	GameTracker gameTracker(&currentMap, &mainCharacter, &friendCharacter, pistol, ammo30, ammo60, medkit, iceDyno, fireDyno, normalTree, burntTree, seaWater);


	//Update inventory
	inv = gameTracker.getInventory();

	// Check if we close the window or press the escape button
	while ( 
		glfwWindowShouldClose(window.getWindow()) == 0)
	{

		inv = gameTracker.getInventory();



		//Handle user input
		window.update(); // This also handles KeyBinds
		window.clear();


		//These are computed at the top (in main loop then shared with other classes)

		float time = glfwGetTime();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		//Handle user input
		processKeyboardInput(camera,mainCharacter, friendCharacter, gameTracker, currentMap, deltaTime);

		//Compute view and projections matrices for MVP
		glm::mat4 ProjectionMatrix = glm::perspective(90.0f, width * 1.0f / height, 0.8f, 10000.0f);
		glm::mat4 ViewMatrix = glm::lookAt(camera.getCameraPosition(), camera.getCameraPosition() + camera.getCameraViewDirection(), camera.getCameraUp());

		

		//Collecting gun or drops from the map
		gameTracker.addToInventory(currentMap.hasToPickupGun());
		gameTracker.addToInventory(currentMap.hasToPickupDrop());

		//Moving everything in the scene (projectiles, celestials, enemies) & Handles collisions with projectiles 
		currentMap.updateScene(deltaTime);

		
		//Game Tracker will check if there's any dead character (2 ways of ending the game)
		taskTitleAndDescription = gameTracker.getCurrentTask(deltaTime);

		//Game Tracker will check if the MC is holding any item
		heldItemNameAndAmount = gameTracker.getEquippedToolDetails();

		//Update inventory
		inventoryItemsAndAmounts = gameTracker.getInventoryItemsAndAmounts();

		//Determine the color of the sky, light and light position
		glm::vec3 lightPos, lightColor;
		glm::vec4 skyColor;

		Celestial::determineTimeAndSetLight(sun, moon, lightColor, lightPos, skyColor);
		glClearColor(skyColor.x, skyColor.y, skyColor.z, skyColor.w);

		//Render the map and all of the models in it
		currentMap.render(ProjectionMatrix, ViewMatrix, lightColor, lightPos, time);
		


		// Render UI last
		window.renderGUI();
	}

	return 0;
}

void processKeyboardInput(Camera& camera,Main_Char& mainCharacter, Friend& friendCharacter, GameTracker& gameTracker, Map& currentMap, float deltaTime)
{
	float cameraSpeed = 30 * deltaTime;
	if (*paused == false) {
		glm::vec3 originalPosition = camera.getCameraPosition();

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
		
		glm::vec3 newPosition = camera.getCameraPosition();
		glm::vec3 desiredMovement = newPosition - originalPosition;

		glm::vec3 correctedMovement =
			currentMap.resolveCameraCollisionSliding(originalPosition, desiredMovement);

		camera.setCameraPosition(originalPosition + correctedMovement);

		double mouseX, mouseY;
		window.getMousePos(mouseX, mouseY);
		camera.setCursorOrientation(mouseX, mouseY);

		// Check if a tool is equipped
		if (spectateMode != nullptr && !(*spectateMode)) {
			auto equippedToolDetails = gameTracker.getEquippedToolDetails();

			// If it's a gun and left mouse button is pressed
			if (equippedToolDetails.first.find("Gun:") != std::string::npos && window.isMousePressed(GLFW_MOUSE_BUTTON_LEFT)) {
				if (gameTracker.getInventory()->gun) {
					glm::vec3 targetPosition = camera.getCameraViewDirection() * 100.0f + camera.getCameraPosition(); 
					
					gameTracker.getInventory()->gun->shoot(currentMap.getProjectilesByType(), targetPosition, glfwGetTime(), gameTracker.getInventory()->ammo);
				}
			}
			// If it's a medkit and left mouse button is pressed
			else if (equippedToolDetails.first.find("Medkit") != std::string::npos && window.isMousePressed(GLFW_MOUSE_BUTTON_LEFT)) {
				mainCharacter.setHealth(50 + mainCharacter.getHealth());
				friendCharacter.setHealth(50 + friendCharacter.getHealth());

				// Remove the medkit after use
				auto& drops = gameTracker.getInventory()->drops;
				for (auto it = drops.begin(); it != drops.end(); ++it) {
					if ((*it)->isEquipped()) {
						drops.erase(it);
						break;
					}
				}
			}
			
		}
	}
}
