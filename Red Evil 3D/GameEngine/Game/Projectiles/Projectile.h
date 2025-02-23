#pragma once
#include "../../Model Loading/mesh.h"
#include "../../Shaders/shader.h"
#include "../../Resources/Model Packs/ProjectilePacks.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Projectile {
private:
    Mesh mesh;
    Shader shader;
    glm::vec3 position;
    glm::vec3 velocity;
    float speed;
    float damage;
    glm::vec3 rotationAngles; // Stores rotation angles for X, Y, Z axes
    float scale;
    float maxDistance;
    float distanceCovered;
    ProjectileType projType;
    std::string name;

public:
    // Constructor
    Projectile(const Mesh& loadedMesh, const Shader& loadedShader, ProjectileType type, glm::vec3 startPos, glm::vec3 direction)
        : mesh(loadedMesh), shader(loadedShader), position(startPos), projType(type), scale(1.0f), maxDistance(0.0f), distanceCovered(0.0f) {

        // Get game-related attributes from your projectile pack (damage, speed, scale, maxDistance, name)
        getProjectileGameAttributes(type, damage, speed, scale, maxDistance, name);

        // Normalize the direction and calculate velocity
        if (glm::length(direction) > 0.0f) {  // Prevent division by zero
            velocity = glm::normalize(direction) * speed;
        } else {
            velocity = glm::vec3(0.0f); // Set velocity to zero if no valid direction
        }

        // Calculate initial rotation angles so the projectile faces the movement direction
        calculateRotationAngles();
    }

    // Move the projectile; returns true if the projectile has exceeded its range.
    bool move(float deltaTime) {
        // Calculate displacement based on the current velocity and elapsed time
        glm::vec3 displacement = velocity * deltaTime;
        position += displacement;

        // Update the total distance covered by the projectile
        distanceCovered += glm::length(displacement);

        // If the projectile traveled beyond its allowed range, return true (indicating removal)
        return (distanceCovered >= maxDistance);
    }

    // Set a new target for the projectile; adjusts velocity and rotation accordingly.
    void setTarget(glm::vec3 targetPosition) {
        // Calculate new direction from the current position to the target
        glm::vec3 direction = targetPosition - position;

        // Normalize the direction and calculate the new velocity
        if (glm::length(direction) > 0.0f) { // Prevent division by zero
            velocity = glm::normalize(direction) * speed;
        }

        // Recalculate rotation angles to match the new velocity
        calculateRotationAngles();
    }

    // Render the projectile using the provided transformation matrices and lighting information.
    void render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::vec3 lightColor, glm::vec3 lightPos, Camera* camera) {
        shader.use();

        // Build the model transformation matrix.
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position); // Apply position
        // Apply rotations (order: X, Y, then Z)
        modelMatrix = glm::rotate(modelMatrix, rotationAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotationAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, rotationAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scale)); // Apply scaling

        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

        // Pass the transformation and lighting uniforms to the shader.
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniform3fv(glGetUniformLocation(shader.getId(), "lightColor"), 1, glm::value_ptr(lightColor));
        glUniform3fv(glGetUniformLocation(shader.getId(), "lightPos"), 1, glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(shader.getId(), "viewPos"), 1, glm::value_ptr(camera->getCameraPosition()));

        // Draw the projectile's mesh.
        mesh.draw(shader);
    }

    // Getters and utility methods.
    glm::vec3 getPosition() const { return position; }
    void setPosition(const glm::vec3& newPos) { position = newPos; }
    float getDamage() const { return damage; }

    // Check if the projectile has exceeded its allowed range.
    bool hasExceededRange() const {
        return distanceCovered >= maxDistance;
    }

    ProjectileType getType() const {
        return projType;
    }

    std::string getName() const {
        return name;
    }

private:
    // Calculate rotation angles based on the current velocity vector.
    void calculateRotationAngles() {
        // Calculate pitch (rotation around the X-axis) using the Y component and horizontal magnitude.
        float pitch = glm::degrees(glm::atan(velocity.y, glm::length(glm::vec2(velocity.x, velocity.z))));
        // Calculate yaw (rotation around the Y-axis) using the X and Z components.
        float yaw = glm::degrees(glm::atan(velocity.x, velocity.z));
        float roll = 0.0f; // Roll is typically zero unless you need a bank effect.

        rotationAngles = glm::vec3(pitch, yaw, roll);
    }
};
