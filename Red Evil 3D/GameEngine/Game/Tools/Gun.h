#pragma once
#include "../../Model Loading/mesh.h"
#include "../../Shaders/shader.h"
#include "../../Resources/Model Packs/GunPacks.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <map>
#include <vector>

class Gun {
private:
    Mesh mesh;
    Shader shader;
    glm::vec3 position;
    std::string name;
    float scale;              // Scaling factor
    float rotationAngle;
    int ammoCount;
    int maxAmmo;
    float damage, fireRate, reloadTime, range;
    float delayBetweenShots, lastShotTime;
    bool equipped;
    float horizontalOffset;   // Horizontal offset (-1: left, 0: middle, 1: right)
    GunPack type;
    float adjustmentSpeed;    // Speed of horizontal offset adjustment
    Projectile projectileTemplate;

public:
    Gun( Mesh& loadedMesh,  Shader& loadedShader, GunPack pack,  Projectile projTemplate)
        : mesh(loadedMesh), shader(loadedShader), position(0.0f), lastShotTime(0.0f),
        rotationAngle(0.0f), equipped(false), horizontalOffset(0.0f), adjustmentSpeed(2.0f),
        projectileTemplate(projTemplate), type(pack), name(""), maxAmmo(0), ammoCount(0) {
        // Get game-related attributes
        getGunGameAttributes(pack, name, damage, fireRate, maxAmmo, reloadTime, range, scale, position);

        delayBetweenShots = 1.0f / fireRate;
    }

    void update( Camera* camera, float deltaTime) {
        if (!camera) return;
        std::cout << "Updating Gun \n";

        // Compute horizontal offset
        float offsetMultiplier = glm::clamp(horizontalOffset, -1.0f, 1.0f); // Clamp value to [-1, 1]
        glm::vec3 offset = glm::vec3(offsetMultiplier * 0.5f, -0.2f, -0.5f); // Adjust horizontal positioning
        position = camera->getCameraPosition() + offset;
    }

    void adjustHorizontalOffset(bool moveRight, float deltaTime) {
        float targetOffset = moveRight ? 1.0f : -1.0f; // Target value based on direction
        horizontalOffset = glm::mix(horizontalOffset, targetOffset, deltaTime * adjustmentSpeed);
    }

    void shoot(std::map<ProjectileType, std::vector<Projectile>>& projectilesByType,  glm::vec3 targetPosition, float currentTime, int& ammo) {
        if (!equipped || ammo <= 0 || currentTime - lastShotTime < delayBetweenShots ) return;
            
        ammo--;
        // Clone the projectile template
        Projectile newProjectile = projectileTemplate;

        // Set the projectile's position to the gun's position
        newProjectile.setPosition(this->position);

        // Set the projectile's direction towards the target position
        glm::vec3 projectileDirection = targetPosition - this->position;
        newProjectile.setTarget(projectileDirection);

        // Add the projectile to the appropriate type in the map
        projectilesByType[projectileTemplate.getType()].push_back(newProjectile);

        // Update ammo count and shot timer
        lastShotTime = currentTime;
    }

    void render( glm::mat4 &projectionMatrix,  glm::mat4 &viewMatrix,  glm::vec3 lightColor,  glm::vec3 lightPos,  Camera* camera) {
        if (camera == nullptr) {
            std::cout << "Camera is nullptr\n";
            return;
        }


        shader.use();

        // Set the model matrix for the gun
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), this->position);
        modelMatrix = glm::rotate(modelMatrix, this->rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(this->scale));

        // Calculate MVP matrix
        glm::mat4 MVP = (projectionMatrix) * (viewMatrix) * modelMatrix;

        // Pass the MVP matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "model"), 1, GL_FALSE, &modelMatrix[0][0]);
        glUniform3fv(glGetUniformLocation(shader.getId(), "lightColor"), 1, glm::value_ptr(lightColor));
        glUniform3fv(glGetUniformLocation(shader.getId(), "lightPos"), 1, glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(shader.getId(), "viewPos"), 1, glm::value_ptr(camera->getCameraPosition()));

        // Draw the mesh
        mesh.draw(shader);
    }

    // Accessors and Mutators
     glm::vec3 getPosition()  { return position; }
    void setPosition( glm::vec3 pos) {  position = pos; }
    void setRotation(float angle) { rotationAngle = angle; }
    bool isEquipped()  { return equipped; }
    void setEquipped(bool status) { equipped = status; }
    void setAmmoCount(int count) { ammoCount = count; }
    int getAmmoCount()  { return ammoCount; }
    void setHorizontalOffset(float offset) { horizontalOffset = glm::clamp(offset, -1.0f, 1.0f); }
    float getHorizontalOffset()  { return horizontalOffset; }
    void setAdjustmentSpeed(float speed) { adjustmentSpeed = glm::max(0.0f, speed); }
    float getAdjustmentSpeed()  { return adjustmentSpeed; }
    int getMaxAmmo()  { return maxAmmo; }
    GunPack getType()  { return type; }
     std::string getName()  { return name; }
};
