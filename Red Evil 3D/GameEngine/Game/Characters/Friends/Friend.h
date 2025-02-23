#pragma once
#include "../../../Model Loading/mesh.h"
#include "../../../Shaders/shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include "../../../Game/Projectiles/Projectile.h"
#include <map>

class Friend {
private:
    Mesh mesh;
    Shader shader;
    glm::vec3 position;
    glm::vec3 offset;
    float scale;
    float health;
    float speed;
    float rotationAngle;
    float fireRate;
    float range;
    float timeSinceLastShot;
    Projectile projectileTemplate;
    std::vector<ProjectileType> vulnerableTo;
public:



    Friend( Mesh& loadedMesh,  Shader& loadedShader, CharacterPack pack, Projectile& projectile)
        : mesh(loadedMesh), shader(loadedShader), projectileTemplate(projectile), rotationAngle(0.0f), timeSinceLastShot(0.0f) {
        float radius;
        glm::vec3 startingPosition, movementAxis;
        MovementType movementType;
  
        getCharacterGameAttributes(pack, health, speed, vulnerableTo,movementAxis,movementType,startingPosition,radius,scale, fireRate, range);
        offset = glm::vec3(2.0f, 0.0f, -2.0f); // Default offset
    }

    void move(glm::vec3 mainCharacterPosition, float deltaTime, std::map<ProjectileType, std::vector<Projectile>>& projectilesByType, glm::vec3 &targetPosition, bool isEnemy) {
        if (health <= 0.0f) return;
        this->position = mainCharacterPosition + offset;

        glm::vec3 directionToTarget = glm::normalize(targetPosition - this->position);
        rotationAngle = glm::degrees(glm::atan(directionToTarget.x, directionToTarget.z));
        if (isEnemy) {
            shoot(deltaTime, projectilesByType, targetPosition);

        }
    }

    void shoot(float deltaTime, std::map<ProjectileType, std::vector<Projectile>>& projectilesByType, glm::vec3& targetPosition) {
        timeSinceLastShot += deltaTime;

        if (timeSinceLastShot >= (1.0f / fireRate) && glm::distance(this->position, targetPosition) <= range) {
			std::cout << "Friend's Target Position is: " << targetPosition.x << " " << targetPosition.y << " " << targetPosition.z << "\n";
            projectileTemplate.setPosition(this->position);

            glm::vec3 directionToTarget = targetPosition - this->position;

            projectileTemplate.setTarget(directionToTarget);
            
            projectilesByType[projectileTemplate.getType()].emplace_back(projectileTemplate);

            timeSinceLastShot = 0.0f;
        }
    }

    void render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::vec3 lightColor, glm::vec3 lightPos, Camera* camera) {
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

    const glm::vec3 getPosition() const { return position; }
    void setPosition( glm::vec3 pos) { position = pos; }

    float getHealth() { return health; }
    void setHealth(float value) { health = value; }

    std::vector<ProjectileType> getVulnerableTo() {
        return vulnerableTo;
    }

    void takeDamage(float damage) {
        health -= damage;                  // Subtract the damage from health
        if (health < 0.0f) health = 0.0f;  // Clamp the health to a minimum of 0.0
    }

    bool isVulnerableTo(ProjectileType projectile)  {
        return std::find(vulnerableTo.begin(), vulnerableTo.end(), projectile) != vulnerableTo.end();
    }
};