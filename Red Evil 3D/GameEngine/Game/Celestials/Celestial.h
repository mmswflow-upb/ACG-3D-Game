#pragma once
#include "../../Model Loading/mesh.h"
#include "../../Shaders/shader.h"
#include "../../Resources/Model Packs/CelestialPacks.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Celestial {
private:
    Mesh mesh;
    Shader shader;
    glm::vec3 currentPosition; // Current position
    glm::vec3 color;           // Color of the celestial object
    float scale;               // Scale factor
    bool visible;
    float orbitRadius;         // Orbit radius from the pack
    float orbitSpeed;          // Orbit speed from the pack
    float currentAngle;        // Current angle for orbit calculation

public:
    Celestial(const Mesh& loadedMesh, const Shader& loadedShader, CelestialPack pack)
        : mesh(loadedMesh), shader(loadedShader), visible(true), currentAngle(0.0f) {

        // Get in-game attributes
        glm::vec3 startingPosition;
        getCelestialGameAttributes(pack, startingPosition, color, scale, orbitRadius, orbitSpeed);
        currentPosition = startingPosition; // Set initial position
    }

    void setPosition(const glm::vec3& pos) { currentPosition = pos; }
    const glm::vec3& getPosition() const { return currentPosition; }

    void update(float deltaTime) {
        currentAngle += orbitSpeed * deltaTime;

        // Calculate circular orbit around XZ plane
        currentPosition.x = orbitRadius * glm::cos(currentAngle);
        currentPosition.z = orbitRadius * glm::sin(currentAngle);
    }

    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
        if (!visible) return;

        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), currentPosition);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

        shader.use();
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
        mesh.draw(shader);
    }
};
