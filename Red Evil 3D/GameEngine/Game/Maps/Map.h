#pragma once
#include <vector>
#include <glm.hpp>
#include <map>
#include <algorithm>
#include "../Characters/Enemies/Enemy.h"
#include "../Characters/Main Character/Main_Char.h"
#include "../Characters/Friends/Friend.h"
#include "../Tools/Drop.h"
#include "../Maps/Objects/Animatable.h" // Make sure this header provides update() and render() methods
#include "../Projectiles/Projectile.h"
#include "../../Shaders/shader.h"
#include "../../Model Loading/mesh.h"
#include "../../Resources/Model Packs/MapPacks.h"
#include "../Celestials/Celestial.h"
#include "../../Game/Tools/Gun.h"

using namespace std;

class Map {
private:
    Enemy* enemy;              // Single enemy
    Friend* friendCharacter;   // Single friend
    Main_Char* mainCharacter;  // Single main character
    Gun* gun;                  // Single gun used by MC
    Gun* gunToBePickedUp;
    std::vector<Drop> drops;
    std::vector<Animatable> animatables; // Container for animatable objects
    std::map<ProjectileType, std::vector<Projectile>> projectilesByType; // Keeps all projectiles that need to be rendered
    Celestial* moon, * sun;
    Camera* camera;
    glm::vec3 position;
    bool* animating;
    bool* spectateMode;
    bool* paused;
    Mesh terrainMesh;
    Shader shader;

public:
    Map(Mesh& loadedMesh, Shader& loadedShader, MapPack pack, Main_Char* mainChar, Friend* fr, Celestial* newSun, Celestial* newMoon, Camera* cam, bool* anim, bool* paus, bool* specMode)
        : terrainMesh(loadedMesh), shader(loadedShader), mainCharacter(mainChar), sun(newSun), moon(newMoon), enemy(nullptr), friendCharacter(fr), camera(cam), animating(anim),
        paused(paus), spectateMode(specMode), gun(nullptr), gunToBePickedUp(nullptr), position(glm::vec3(0.1f, 0.1f, 0.1f)) {
    }

    // Function to update everything in the scene
    void updateScene(float deltaTime) {
        // Update enemy if it exists
        if (paused != nullptr && spectateMode != nullptr) {
            if (*paused == true || *spectateMode == true) return;
        }

        mainCharacter->move(camera);

        if (enemy != nullptr) {
            enemy->move(deltaTime, projectilesByType, mainCharacter->getPosition());
            friendCharacter->move(mainCharacter->getPosition(), deltaTime, projectilesByType, enemy->getPosition(), true);
        }
        else {
            glm::vec3 targetPosition;
            bool targetPositionInitialized = false;
            // Determine the closest object (gun or drop) to the main character
            float closestDistance = std::numeric_limits<float>::max(); // Initialize with maximum possible value

            // Prioritize the gun, the friend will orient itself towards guns first then drops
            if (gunToBePickedUp != nullptr) {
                float gunDistance = glm::distance(mainCharacter->getPosition(), gunToBePickedUp->getPosition());
                if (gunDistance < closestDistance) {
                    closestDistance = gunDistance;
                    targetPosition = gunToBePickedUp->getPosition();
                    targetPositionInitialized = true;
                }
            }
            else {
                // Check the drops
                for (auto& drop : drops) {
                    float dropDistance = glm::distance(mainCharacter->getPosition(), drop.getPosition());
                    if (dropDistance < closestDistance) {
                        closestDistance = dropDistance;
                        targetPosition = drop.getPosition();
                        targetPositionInitialized = true;
                    }
                }
            }

            // No guns or drops found - default target to main character's position
            if (!targetPositionInitialized) {
                targetPosition = mainCharacter->getPosition();
            }

            // Pass the closest object's position to the friend character
            friendCharacter->move(mainCharacter->getPosition(), deltaTime, projectilesByType, targetPosition, false);
        }

        // Update MC's gun if equipped
        if (gun != nullptr) {
            if (gun->isEquipped()) {
                gun->update(camera, deltaTime);
            }
        }

        // Update projectiles
        moveProjectiles(deltaTime);

        // Update animatable objects if animating liquids are enabled
        if ((*animating) == true) {
            for (auto& animatable : animatables) {
                animatable.update(deltaTime);
            }
        }

        // Update celestials
        moveCelestials(deltaTime);

        checkProjectileCollisions();
        removeOutOfRangeProjectiles();
    }

    // Method to add an animatable object to the map
    void addAnimatable(const Animatable& animatable) {
        animatables.push_back(animatable);
    }

    void setGun(Gun* newGun) {
        cout << "Set new gun\n";
        gun = newGun;
    }

	void removeGunToBePickedUp() {
		gunToBePickedUp = nullptr;
	}

    Enemy* getEnemy() { return enemy; }
    void setEnemy(Enemy* newEnemy) { enemy = newEnemy; cout << "Setting new Enemy in Map\n"; }

    Gun* getGunToBePickedUp() { return gunToBePickedUp; }
    void setGunToBePickedUp(Gun& newGun) {
        gunToBePickedUp = &newGun;

		glm::vec3 gunPos = gunToBePickedUp->getPosition();

        cout << "Set Gun To Be Picked Up: X: " << gunPos.x << " Y: " << gunPos.y << " Z: " << gunPos.z << "\n";
    }

    std::vector<Drop>* getDrops() { return &drops; }
    void addDrop(Drop* drop) { drops.push_back(*drop); }

    std::map<ProjectileType, std::vector<Projectile>>& getProjectilesByType() { return projectilesByType; }

    // Render the map (for completeness)
    void render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::vec3 lightColor, glm::vec3 lightPos, float glfwTime) {
        shader.use();

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "model"), 1, GL_FALSE, &modelMatrix[0][0]);
        glUniform3fv(glGetUniformLocation(shader.getId(), "lightColor"), 1, glm::value_ptr(lightColor));
        glUniform3fv(glGetUniformLocation(shader.getId(), "lightPos"), 1, glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(shader.getId(), "viewPos"), 1, glm::value_ptr(camera->getCameraPosition()));

        terrainMesh.draw(shader);

        // Render enemy
        if (enemy != nullptr) {
            enemy->render(projectionMatrix, viewMatrix, lightColor, lightPos, camera);
        }

        // Render friend
        friendCharacter->render(projectionMatrix, viewMatrix, lightColor, lightPos, camera);

        // Render main character
        mainCharacter->render(projectionMatrix, viewMatrix, lightColor, lightPos, camera);

        // Render MC's gun
        if (gun != nullptr) {
            if (gun->isEquipped()) {
                gun->render(projectionMatrix, viewMatrix, lightColor, lightPos, camera);
            }
        }

        if (gunToBePickedUp != nullptr) {
            gunToBePickedUp->render(projectionMatrix, viewMatrix, lightColor, lightPos, camera);
        }

        // Render drops
        for (auto& drop : drops) {
            drop.render(projectionMatrix, viewMatrix, lightColor, lightPos, camera);
        }

        // Render animatable objects
        for (auto& animatable : animatables) {
            animatable.render(projectionMatrix, viewMatrix, lightColor, lightPos, camera, glfwTime, animating);
        }

        // Render projectiles
        for (auto& pair : projectilesByType) {
            for (auto& projectile : pair.second) {
                projectile.render(projectionMatrix, viewMatrix, lightColor, lightPos, camera);
            }
        }

        // Render celestials
        moon->render(projectionMatrix, viewMatrix);
        sun->render(projectionMatrix, viewMatrix);
    }

	void removeAmmoDrops() {
		drops.erase(
			std::remove_if(
				drops.begin(),
				drops.end(),
				[](Drop& drop) {
					return drop.getType() == DropType::Ammo_30 || drop.getType() == DropType::Ammo_60;
				}
			),
			drops.end()
		);
	}

    // Function to remove a specific drop from the map
    void removeDrop(const Drop& removedDrop) {
        // Use the erase-remove idiom to remove the drop
        drops.erase(
            std::remove_if(
                drops.begin(),
                drops.end(),
                [&removedDrop](const Drop& drop) {
                    return &drop == &removedDrop; // Compare using pointers
                }
            ),
            drops.end()
        );
    }

    // In your Map class:
    glm::vec3 resolveCameraCollisionSliding(const glm::vec3& originalPos,
        const glm::vec3& desiredMovement)
    {
        // We'll assume a radius for the camera (main character).
        const float cameraRadius = 1.0f;

        // Start with the movement the player intended.
        glm::vec3 finalMovement = desiredMovement;

        // We'll do a single pass over all animatables for demonstration.
        // For more complex collisions (multiple objects), you might need multiple iterations.
        for (auto& animatable : animatables) {
            glm::vec3 obstaclePos = animatable.getPosition();
            const float obstacleRadius = 1.0f; // Adjust if your animatable has different collision sizes

            // Compute where the camera would end up if we apply finalMovement
            glm::vec3 newCameraPos = originalPos + finalMovement;

            // Check if there's a collision (sphere vs sphere test)
            float distance = glm::distance(newCameraPos, obstaclePos);
            float minDistance = cameraRadius + obstacleRadius;

            if (distance < minDistance) {
                // We have a collision. Let's compute how much we're penetrating the obstacle.
                float penetration = minDistance - distance;

                // Collision normal: from obstacle to newCameraPos
                glm::vec3 collisionNormal = glm::normalize(newCameraPos - obstaclePos);

                // 1) Push the camera out so it doesn't overlap
                // This ensures the camera is just outside the obstacle sphere
                newCameraPos += collisionNormal * penetration;

                // 2) Compute the movement difference after pushing out
                // This effectively "slides" the camera along the surface by removing
                // the normal component that goes into the obstacle.
                glm::vec3 newMovement = newCameraPos - originalPos;

                // Update finalMovement with the corrected movement
                finalMovement = newMovement;
            }
        }
        return finalMovement;
    }



    // Check if character collides with a gun that has to be picked up
    Gun* hasToPickupGun() {
        if (gunToBePickedUp == nullptr) return nullptr;

        float collisionThreshold = 5.0f; // Define the collision distance
        glm::vec3 mainCharPosition = mainCharacter->getPosition();
        glm::vec3 gunPosition = gunToBePickedUp->getPosition();

        if (glm::distance(mainCharPosition, gunPosition) <= collisionThreshold) {
            std::cout << "Gun picked up: " << gunToBePickedUp->getName() << "\n";
            return gunToBePickedUp; // Gun is ready to be picked up
        }
        return nullptr; // No collision
    }

    // Check if character collides with a drop that has to be picked up
    Drop* hasToPickupDrop() {
        float collisionThreshold = 5.0f; // Define the collision distance
        glm::vec3 mainCharPosition = mainCharacter->getPosition();

        for (auto& drop : drops) {
            glm::vec3 dropPosition = drop.getPosition();
            if (glm::distance(mainCharPosition, dropPosition) <= collisionThreshold) {
                std::cout << "Drop picked up: " << drop.getName() << "\n";
                return &drop; // Drop is ready to be picked up
            }
        }
        return nullptr; // No collision
    }

    Main_Char* getMainCharacter() { return mainCharacter; }
    Friend* getFriend() { return friendCharacter; }

private:
    // Move projectiles
    void moveProjectiles(float deltaTime) {
        for (auto& pair : projectilesByType) {
            for (auto& projectile : pair.second) {
                projectile.move(deltaTime);
            }
        }
    }

    // Move celestial objects
    void moveCelestials(float deltaTime) {
        sun->move(deltaTime);
        moon->move(deltaTime, sun->getAngle());
    }

    // Check if there's any projectiles colliding with any characters, in order to apply damage
    void checkProjectileCollisions() {
        float collisionThreshold = 5.0f; // Radius for collision detection

        // Check collisions with the main character
        auto& mainCharacterVulnerableTo = mainCharacter->getVulnerableTo();
        for (auto& type : mainCharacterVulnerableTo) {
            auto& projectiles = projectilesByType[type];
            projectiles.erase(
                std::remove_if(
                    projectiles.begin(),
                    projectiles.end(),
                    [this, collisionThreshold](Projectile& projectile) {
                        if (glm::distance(mainCharacter->getPosition(), projectile.getPosition()) <= collisionThreshold) {
                            mainCharacter->takeDamage(projectile.getDamage());
                            return true; // Remove projectile
                        }
                        return false;
                    }
                ),
                projectiles.end()
            );
        }

        // Check collisions with the friend character
        auto& friendVulnerableTo = friendCharacter->getVulnerableTo();
        for (auto& type : friendVulnerableTo) {
            auto& projectiles = projectilesByType[type];
            projectiles.erase(
                std::remove_if(
                    projectiles.begin(),
                    projectiles.end(),
                    [this, collisionThreshold](Projectile& projectile) {
                        if (glm::distance(friendCharacter->getPosition(), projectile.getPosition()) <= collisionThreshold) {
                            std::cout << "Friend took damage: " << projectile.getDamage() << " Name: " << projectile.getName() << "\n";
                            friendCharacter->takeDamage(projectile.getDamage());
                            return true; // Remove projectile
                        }
                        return false;
                    }
                ),
                projectiles.end()
            );
        }

        // Check collisions with the enemy (if it exists)
        if (enemy) {
            const auto& enemyVulnerableTo = enemy->getVulnerableTo();
            for (const auto& type : enemyVulnerableTo) {
                auto& projectiles = projectilesByType[type];
                projectiles.erase(
                    std::remove_if(
                        projectiles.begin(),
                        projectiles.end(),
                        [this, collisionThreshold](Projectile& projectile) {
                            if (glm::distance(enemy->getPosition(), projectile.getPosition()) <= collisionThreshold) {
                                enemy->takeDamage(projectile.getDamage());
                                return true; // Remove projectile
                            }
                            return false;
                        }
                    ),
                    projectiles.end()
                );
            }
        }
    }

    


    // Remove projectiles that go beyond their range
    void removeOutOfRangeProjectiles() {
        for (auto& pair : projectilesByType) {
            auto& projectiles = pair.second;
            projectiles.erase(
                std::remove_if(
                    projectiles.begin(),
                    projectiles.end(),
                    [](const Projectile& projectile) {
                        return projectile.hasExceededRange();
                    }
                ),
                projectiles.end()
            );
        }
    }
};
