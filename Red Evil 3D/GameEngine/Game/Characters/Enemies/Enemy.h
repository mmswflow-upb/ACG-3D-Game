#pragma once
#include "../../../Model Loading/mesh.h"
#include "../../../Shaders/shader.h"
#include "../../../Resources/Model Packs/CharacterPacks.h"
#include "../../../Camera/camera.h"
#include "../../../Game/Projectiles/Projectile.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include <map>

class Enemy {
private:
    Mesh mesh;
    Shader shader;
    glm::vec3 position;
    glm::vec3 startingPosition;
    glm::vec3 movementAxis;    // Axis of movement
    float scale;
    float health;
    float speed;
    float angle;               // Angle for circular movement
    float radius;              // Radius or limit for movement
    float rotationAngle;               // Angle for circular movement
    float movementLimit;       // Limit for straight or circular movement
    MovementType movementType; // Movement type (Straight or Circular)
    std::vector<ProjectileType> vulnerableTo;
    Projectile projectileTemplate;
    float distanceTraveled;    // Tracks how far the enemy has moved on the axis
    float timeSinceLastShot;
    float fireRate;
    float range;
    CharacterPack charType;

public:
    Enemy(const Mesh& loadedMesh, const Shader& loadedShader, CharacterPack pack, Projectile projTemp)
        : mesh(loadedMesh), shader(loadedShader), angle(0.0f), distanceTraveled(0.0f), rotationAngle(0.0f), timeSinceLastShot(0.0f) , projectileTemplate(projTemp), charType(pack), movementLimit(0.0f){
        glm::vec3 initialMovementAxis;
        std::vector<ProjectileType> vulnerabilities;

        // Retrieve attributes from the game data pack
        getCharacterGameAttributes(pack, health, speed, vulnerabilities, initialMovementAxis, movementType, startingPosition, radius, scale, fireRate, range);

        this->health = health;
        this->speed = speed;
        this->vulnerableTo = vulnerabilities;
        this->movementAxis = glm::normalize(initialMovementAxis);
        this->position = startingPosition;
    }

   

    void move(float deltaTime, std::map<ProjectileType, std::vector<Projectile>>& projectilesByType, glm::vec3& targetPosition) {
        if (health <= 0.0f) return;

        glm::vec3 directionToTarget = glm::normalize(targetPosition - this->position);
        rotationAngle = glm::degrees(glm::atan(directionToTarget.x, directionToTarget.z));

        if (movementType == MovementType::Straight) {
            glm::vec3 displacement = movementAxis * speed * deltaTime;
            this->position += displacement;
            if (glm::length(position - startingPosition) >= radius) {
                movementAxis = -movementAxis; // Reverse direction
            }
        }
        else if (movementType == MovementType::Circular) {
            angle += speed * deltaTime;
            if (angle > 360.0f) angle -= 360.0f;
            this->position.x = startingPosition.x + radius * glm::cos(angle);
            this->position.z = startingPosition.z + radius * glm::sin(angle);
        }

        shoot(deltaTime, projectilesByType, targetPosition);
    }

    void shoot(float deltaTime, std::map<ProjectileType, std::vector<Projectile>>& projectilesByType, glm::vec3& targetPosition) {



        timeSinceLastShot += deltaTime;

        if (timeSinceLastShot >= (1.0f / fireRate) && glm::distance(this->position, targetPosition) <= range) {
            std::cout << "Enemy's Target Position is: " << targetPosition.x << " " << targetPosition.y << " " << targetPosition.z << "\n";

            projectileTemplate.setPosition(this->position);
            glm::vec3 directionToTarget = targetPosition - this->position;

            projectileTemplate.setTarget(directionToTarget);

            projectilesByType[projectileTemplate.getType()].emplace_back(projectileTemplate);

            timeSinceLastShot = 0.0f;
        }
    }

    void render( glm::mat4& projectionMatrix,  glm::mat4& viewMatrix, glm::vec3 lightColor, glm::vec3 lightPos, Camera* camera) {
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

    float getHealth() { return health; }
    void setHealth(float value) { health = value; }

     glm::vec3 getMovementAxis()  { return movementAxis; }
    void setMovementAxis( glm::vec3 axis) { movementAxis = glm::normalize(axis); }

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

    CharacterPack getType() {
        return charType;
    }
};
