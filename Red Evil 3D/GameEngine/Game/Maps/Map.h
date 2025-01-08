#pragma once
#include <vector>
#include <glm.hpp>
#include <map>
#include <algorithm>
#include "../Characters/Enemies/Enemy.h"
#include "../Characters/Main Character/Main_Char.h"
#include "../Characters/Friends/Friend.h"
#include "../Tools/Drop.h"
#include "../Maps/Objects/Animatable.h"
#include "../Projectiles/Projectile.h"
#include "../../Shaders/shader.h"
#include "../../Model Loading/mesh.h"
#include "../../Resources/Model Packs/MapPacks.h"
#include "../Celestials/Celestial.h"


class Map {
private:
    std::vector<Enemy> enemies;
    Main_Char mainCharacter;  // Single main character
    std::vector<Friend> friends;
    std::vector<Drop> drops;
    std::vector<Animatable> animatables;
    std::vector<Projectile> projectiles;
    std::vector<Celestial> celestials;
    // Map projectiles by their type
    std::map<ProjectileType, std::vector<Projectile>> projectilesByType;

    glm::vec3 position;

    Mesh terrainMesh;
    Shader shader;

public:
    Map(const Mesh& loadedMesh, const Shader& loadedShader, MapPack pack, const Main_Char& mainChar)
        : terrainMesh(loadedMesh), shader(loadedShader), mainCharacter(mainChar) {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    // Add methods
    void addEnemy(const Enemy& enemy) { enemies.push_back(enemy); }
    void addFriend(const Friend& friendChar) { friends.push_back(friendChar); }
    void addDrop(const Drop& drop) { drops.push_back(drop); }
    void addAnimatable(const Animatable& animatable) { animatables.push_back(animatable); }
    void addCelestial(const Celestial& celestial) { celestials.push_back(celestial); }
    void addProjectile(Projectile& projectile) {
        projectilesByType[projectile.getType()].push_back(projectile);
    }

    // Clear methods
    void clearEnemies() { enemies.clear(); }
    void clearFriends() { friends.clear(); }
    void clearDrops() { drops.clear(); }
    void clearAnimatables() { animatables.clear(); }
    void clearProjectiles() { projectilesByType.clear(); }

    // Update projectiles
    void moveProjectiles(float deltaTime) {
        for (auto& pair : projectilesByType) {
            auto& projectiles = pair.second;
            for (auto& projectile : projectiles) {
                projectile.move(deltaTime);
            }
        }
    }

   

    // Move enemies
    void moveEnemies(float deltaTime) {
        for (auto& enemy : enemies) {
            // Add specific enemy movement logic here
        }
    }

    // Move friends
    void moveFriends(float deltaTime) {
        for (auto& friendChar : friends) {
            // Add specific friend movement logic here
        }
    }

    // Move celestials
    void moveCelestials(float deltaTime) {
        for (auto& celestial : celestials) {
            celestial.update(deltaTime);
        }
    }

    // Check bounds or obstacles collisions for the main character
    void checkObstacleCollisions() {

    }

    // Check projectile collisions
    void checkProjectileCollisions() {
        // Check for collisions with enemies
        for (auto& enemy : enemies) {
            const auto& vulnerableTo = enemy.getVulnerableTo();
            for (const auto& type : vulnerableTo) {
                auto& projectiles = projectilesByType[type];
                projectiles.erase(
                    std::remove_if(projectiles.begin(), projectiles.end(),
                        [&enemy](const Projectile& projectile) {
                            if (glm::distance(enemy.getPosition(), projectile.getPosition()) < 1.0f) {
                                enemy.takeDamage(projectile.getDamage());
                                return true; // Remove projectile
                            }
                            return false;
                        }),
                    projectiles.end());
            }
        }

        // Check for collisions with friends
        for (auto& friendChar : friends) {
            const auto& vulnerableTo = friendChar.getVulnerableTo();
            for (const auto& type : vulnerableTo) {
                auto& projectiles = projectilesByType[type];
                projectiles.erase(
                    std::remove_if(projectiles.begin(), projectiles.end(),
                        [&friendChar](const Projectile& projectile) {
                            if (glm::distance(friendChar.getPosition(), projectile.getPosition()) < 1.0f) {
                                friendChar.takeDamage(projectile.getDamage());
                                return true; // Remove projectile
                            }
                            return false;
                        }),
                    projectiles.end());
            }
        }

        // Check for collisions with main character
        const auto& vulnerableTo = mainCharacter.getVulnerableTo();
        for (const auto& type : vulnerableTo) {
            auto& projectiles = projectilesByType[type];
            projectiles.erase(
                std::remove_if(projectiles.begin(), projectiles.end(),
                    [this](const Projectile& projectile) {
                        if (glm::distance(mainCharacter.getPosition(), projectile.getPosition()) < 1.0f) {
                            mainCharacter.takeDamage(projectile.getDamage());
                            return true; // Remove projectile
                        }
                        return false;
                    }),
                projectiles.end());
        }
    }

    // Render the map
    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix, glm::vec3 lightColor, glm::vec3 lightPos, Camera& camera, bool spectateMode, bool animatingLiquids, double glfwTime) {
        shader.use();

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(position);
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

        terrainMesh.draw(shader);

        // Render enemies
        for (auto& enemy : enemies) {
            enemy.render(projectionMatrix, viewMatrix, lightColor, lightPos, camera);
        }

        // Render main character
        mainCharacter.render(projectionMatrix, viewMatrix, lightColor, lightPos, camera);

        // Render friends
        for (auto& friendChar : friends) {
            friendChar.render(projectionMatrix, viewMatrix, lightColor, lightPos, camera);
        }

        // Render drops
        for (auto& drop : drops) {
            drop.render(projectionMatrix, viewMatrix, lightColor, lightPos, camera);
        }

        // Render animatables
        for (auto& animatable : animatables) {
            animatable.render(projectionMatrix, viewMatrix, lightColor, lightPos, camera, glfwTime);
        }

        // Render projectiles
        for (auto& pair : projectilesByType) {
            for (auto& projectile : pair.second) {
                projectile.render(projectionMatrix, viewMatrix, lightColor, lightPos, camera);
            }
        }
        //Render celestials (sun and moon)
        for (auto& celestial : celestials) {
            celestial.render(projectionMatrix, viewMatrix);
        }
    }

    // Setters
    void setPosition(const glm::vec3& newPos) { position = newPos; }

    // Getters
    const std::vector<Enemy>& getEnemies() const { return enemies; }
    const Main_Char& getMainCharacter() const { return mainCharacter; }
    const std::vector<Friend>& getFriends() const { return friends; }
    const std::vector<Drop>& getDrops() const { return drops; }
    const std::vector<Animatable>& getAnimatables() const { return animatables; }
    const std::map<ProjectileType, std::vector<Projectile>>& getProjectilesByType() const { return projectilesByType; }
    glm::vec3 getPosition() const { return position; }
};
