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
    float scale;
    glm::vec3 startingPosition;
    std::vector<ProjectileType> vulnerableTo;

public:

    Main_Char( Mesh& loadedMesh,  Shader& loadedShader, CharacterPack pack)
        : mesh(loadedMesh), shader(loadedShader), rotationAngle(0.0f) {
        float range, radius;
        glm::vec3 movementAxis;
        MovementType movementType;
        float fireRate;

        getCharacterGameAttributes(pack, health, speed, vulnerableTo,movementAxis,movementType,startingPosition,radius,scale, fireRate,range);
    }

    void move( Camera* camera) {
        if (health <= 0.0f) return;
        glm::vec3 cameraPosition = camera->getCameraPosition();
        cameraPosition.y = 20.0f;
        position = cameraPosition;

        glm::vec3 cameraForward = camera->getCameraViewDirection();
        rotationAngle = glm::degrees(glm::atan(cameraForward.x, cameraForward.z));
    }

    void render( glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::vec3 lightColor, glm::vec3 lightPos, Camera* camera) {
        shader.use();

        // Set the model matrix for the drop

        glm::mat4 modelMatrix;
        modelMatrix = glm::translate(glm::mat4(1.0f), this->position);
        modelMatrix = glm::rotate(modelMatrix, this->rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));

        // Calculate MVP matrix
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

        // Pass the MVP matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "model"), 1, GL_FALSE, &modelMatrix[0][0]);
        glUniform3fv(glGetUniformLocation(shader.getId(), "lightColor"), 1, glm::value_ptr(lightColor));
        glUniform3fv(glGetUniformLocation(shader.getId(), "lightPos"), 1, glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(shader.getId(), "viewPos"), 1, glm::value_ptr(camera->getCameraPosition()));

        // Draw the mesh
        mesh.draw(shader);
    }


    glm::vec3 getPosition()  { return position; }
    void setPosition( glm::vec3 pos) { position = pos; }



    float& getHealth()  { return health; }
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



    bool isVulnerableTo(ProjectileType projectile)  {
        return std::find(vulnerableTo.begin(), vulnerableTo.end(), projectile) != vulnerableTo.end();
    }
};
