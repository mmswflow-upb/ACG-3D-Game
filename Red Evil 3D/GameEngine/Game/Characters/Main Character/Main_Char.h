#pragma once
#include "../../Model Loading/mesh.h"
#include "../../Shaders/shader.h"
#include "../../Camera/camera.h"
#include "../../Resources/Model Packs/CharacterPacks.h"
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
    std::vector<ProjectileType> vulnerableTo;

public:
    Main_Char(const Mesh& loadedMesh, const Shader& loadedShader, CharacterPack pack)
        : mesh(loadedMesh), shader(loadedShader) {
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

    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
        shader.use();
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
        mesh.draw(shader);
    }

    const glm::vec3& getPosition() const { return position; }
    void setPosition(const glm::vec3& pos) { position = pos; }

    float getHealth() const { return health; }
    void setHealth(float value) { health = value; }

    bool isVulnerableTo(ProjectileType projectile) const {
        return std::find(vulnerableTo.begin(), vulnerableTo.end(), projectile) != vulnerableTo.end();
    }
};
