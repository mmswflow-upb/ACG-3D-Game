#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "../../Model Loading/mesh.h"
#include "../../Shaders/shader.h"
#include "../../Resources/Model Packs/CelestialPacks.h"

class Celestial {
private:
    Mesh mesh;
    Shader shader;              // Shader for the celestial object
    CelestialAttributes attributes;
    bool visible;
    float orbitRadius;          // Radius of the circular orbit
    float orbitSpeed;           // Speed of rotation (angle increment per frame)
    float currentAngle;         // Current angle in radians

public:
    Celestial(Mesh loadedMesh, Shader shader, CelestialPack pack, float radius, float speed)
        : mesh(loadedMesh),
        shader(shader),
        attributes(getCelestialAttributes(pack)),
        visible(true),
        orbitRadius(radius),
        orbitSpeed(speed),
        currentAngle(0.0f) {
    }

    void update(float deltaTime) {
        // Update the current angle based on the orbit speed and delta time
        currentAngle += orbitSpeed * deltaTime;

        // Keep the angle within the range [0, 2π] for numerical stability
        if (currentAngle > 2.0f * glm::pi<float>()) {
            currentAngle -= 2.0f * glm::pi<float>();
        }

        // Calculate the new position in the circular orbit
        attributes.position.x = orbitRadius * glm::cos(currentAngle);
        attributes.position.y = orbitRadius * glm::sin(currentAngle);
        // Z remains constant for circular orbit around the Z-axis
    }

    void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
        if (!visible) return;

        // Set up the model matrix
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), attributes.position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(attributes.scale));

        // Combine into MVP
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

        // Use shader and set uniform values
        shader.use();
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);

        // Render the celestial object
        mesh.draw(shader);
    }

    const glm::vec3& getPosition() const { return attributes.position; }
    void setPosition(const glm::vec3& newPosition) { attributes.position = newPosition; }

    void setVisible(bool isVisible) { visible = isVisible; }
};
