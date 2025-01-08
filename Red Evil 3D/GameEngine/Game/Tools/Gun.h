#pragma once
#include "../../Model Loading/mesh.h"
#include "../../Shaders/shader.h"
#include "../../Camera/camera.h"
#include "../../Resources/Model Packs/GunPacks.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Gun {
private:
    Mesh mesh;
    Shader shader;
    glm::vec3 position;
    float delayBetweenShots;
    float lastShotTime;
    int ammoCount;
    bool isRightSide; // Determines gun placement (left/right of the camera)
    float damage;
    float fireRate;
    float reloadTime;
    float range;

public:
    Gun(const Mesh& loadedMesh, const Shader& loadedShader, GunPack pack, bool rightSide)
        : mesh(loadedMesh), shader(loadedShader), isRightSide(rightSide), lastShotTime(0.0f) {

        // Get model-related attributes
        auto modelAttributes = getGunModelAttributes(pack);

        // Get game-related attributes
        getGunGameAttributes(pack, damage, fireRate, ammoCount, reloadTime, range);

        delayBetweenShots = 1.0f / fireRate;
        position = glm::vec3(0.0f);
    }

    void update(const Camera& camera) {
        glm::vec3 offset = isRightSide ? glm::vec3(0.5f, -0.2f, -0.5f) : glm::vec3(-0.5f, -0.2f, -0.5f);
        position = camera.getCameraPosition() + offset;
    }

    bool canShoot(float currentTime) const {
        return (currentTime - lastShotTime >= delayBetweenShots && ammoCount > 0);
    }

    void shoot(float currentTime) {
        if (canShoot(currentTime)) {
            lastShotTime = currentTime;
            --ammoCount;
        }
    }

    void reload(int ammo) {
        ammoCount = std::min(ammoCount + ammo, static_cast<int>(fireRate * reloadTime)); // Cap at max ammo
    }

    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
        shader.use();
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
        mesh.draw(shader);
    }

    const glm::vec3& getPosition() const { return position; }
    int getAmmoCount() const { return ammoCount; }
    void setRightSide(bool rightSide) { isRightSide = rightSide; }
};
