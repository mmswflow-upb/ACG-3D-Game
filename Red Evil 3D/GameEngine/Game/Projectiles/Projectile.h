#pragma once
#include "../../Model Loading/mesh.h"
#include "../../Shaders/shader.h"
#include "../../Resources/Model Packs/ProjectilePacks.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Projectile {
private:
    Mesh mesh;
    Shader shader;
    glm::vec3 position;
    glm::vec3 velocity;
    float damage;
    ProjectileType projType;

public:
    Projectile(const Mesh& loadedMesh, const Shader& loadedShader, ProjectileType type, const glm::vec3& startPos, const glm::vec3& direction)
        : mesh(loadedMesh), shader(loadedShader), position(startPos), projType(type) {

        // Get game-related attributes
        float speed;
        getProjectileGameAttributes(type, damage, speed);

        // Calculate velocity
        velocity = glm::normalize(direction) * speed;
    }

    void move(float deltaTime) {
        position += velocity * deltaTime;
    }

    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix, glm::vec3 lightColor, glm::vec3 lightPos, Camera& camera) {
        shader.use();

        // Set the model matrix for the drop
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);

        // Calculate MVP matrix
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

        // Pass the MVP matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

        // Draw the mesh
        mesh.draw(shader);
    }

    const glm::vec3& getPosition() const { return position; }
    float getDamage() const { return damage; }

    ProjectileType getType() {
        return projType;
    }
};
