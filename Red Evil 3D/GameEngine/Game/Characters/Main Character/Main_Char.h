#pragma once
#include "../../../Model Loading/mesh.h"
#include "../../../Shaders/shader.h"
#include "../../../Camera/camera.h"
#include "../../../Resources/Model Packs/CharacterPacks.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>


class Main_Char {
private:
    Mesh mesh;
    Shader shader;
    glm::vec3 position;
    float health;
    float speed;
    float rotationAngle;
    std::vector<ProjectileType> vulnerableTo;

public:
    Main_Char(const Mesh& loadedMesh, const Shader& loadedShader, CharacterPack pack)
        : mesh(loadedMesh), shader(loadedShader) , rotationAngle(0.0f) {
        float health, speed;
        std::vector<ProjectileType> vulnerabilities;
        getCharacterGameAttributes(pack, health, speed, vulnerabilities);

        this->health = health;
        this->speed = speed;
        this->vulnerableTo = vulnerabilities;
        position = glm::vec3(0.0f);
    }

    void move(float deltaTime, const glm::vec3& direction) {
        glm::vec3 normalizedDirection = glm::normalize(direction);
        position += normalizedDirection * speed * deltaTime;
    }

    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix, glm::vec3 lightColor, glm::vec3 lightPos, Camera& camera) {
        shader.use();

        // Set the model matrix for the drop
       
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), this->position);
        modelMatrix =  glm::rotate(modelMatrix, this->rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        
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
    void setPosition(glm::vec3 pos) { this->position = pos;  }

    float getHealth() const { return health; }
    void setHealth(float value) { health = value; }

    std::vector<ProjectileType> getVulnerableTo() {
        return vulnerableTo;
    }

    void takeDamage(float damage) {
        health -= damage;                  // Subtract the damage from health
        if (health < 0.0f) health = 0.0f;  // Clamp the health to a minimum of 0.0
    }
    void setRotation(float angle) {
        this->rotationAngle = angle; // Store the rotation angle (in radians or degrees)
    }



    bool isVulnerableTo(ProjectileType projectile) const {
        return std::find(vulnerableTo.begin(), vulnerableTo.end(), projectile) != vulnerableTo.end();
    }
};
