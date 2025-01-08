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

        // Calculate circular orbit around YZ plane
        currentPosition.y = orbitRadius * glm::cos(currentAngle);
        currentPosition.z = orbitRadius * glm::sin(currentAngle);
    }


    float getTime() const {
        // Return the normalized time (0.0 to 1.0) based on the current angle in the orbit
        return currentAngle / (2.0f * glm::pi<float>());
    }

    static void determineTimeAndSetLight(Celestial& sun, Celestial& moon, glm::vec3& lightColor, glm::vec3& lightPos) {
        float sunTime = sun.getTime(); // Sun's position in the orbit
        float moonTime = moon.getTime(); // Moon's position in the orbit

        // Normalize time (0 to 1) to divide the orbit into day and night
        bool isDay = (sunTime >= 0.25f && sunTime <= 0.75f); // Sun dominates during this range

        if (isDay) {
            // Daytime: Sun is the light source
            lightColor = glm::vec3(1.0f, 0.9f, 0.7f); // Bright yellowish light
            lightPos = sun.getPosition();
        }
        else {
            // Nighttime: Moon is the light source
            lightColor = glm::vec3(0.7f, 0.7f, 1.0f); // Soft bluish light
            lightPos = moon.getPosition();
        }
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
