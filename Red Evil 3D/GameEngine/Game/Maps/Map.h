#pragma once
#include <vector>
#include <glm.hpp>
#include "../Characters/Enemies/Enemy.h"
#include "../Characters/Main Character/Main_Char.h"
#include "../Characters/Friends/Friend.h"
#include "../Tools/Drop.h"
#include "../Maps/Objects/Animatable.h"
#include "../Projectiles/Projectile.h"
#include "../../Shaders/shader.h"
#include "../../Model Loading/mesh.h"
#include "../../Resources/Model Packs/MapPacks.h"

class Map {
private:
    std::vector<Enemy> enemies;
    std::vector<Main_Char> mainCharacters;
    std::vector<Friend> friends;
    std::vector<Drop> drops;
    std::vector<Animatable> animatables;
    std::vector<Projectile> projectiles;

    Mesh terrainMesh;
    Shader shader;
    glm::vec3 ambientColor;

public:
    Map(const Mesh& loadedMesh, const Shader& loadedShader, MapPack pack)
        : terrainMesh(loadedMesh), shader(loadedShader) {
        auto attributes = getMapModelAttributes(pack);
        ambientColor = attributes.ambientColor;
    }

    // Add methods
    void addEnemy(const Enemy& enemy) { enemies.push_back(enemy); }
    void addMainCharacter(const Main_Char& mainChar) { mainCharacters.push_back(mainChar); }
    void addFriend(const Friend& friendChar) { friends.push_back(friendChar); }
    void addDrop(const Drop& drop) { drops.push_back(drop); }
    void addAnimatable(const Animatable& animatable) { animatables.push_back(animatable); }
    void addProjectile(const Projectile& projectile) { projectiles.push_back(projectile); }

    // Clear methods
    void clearEnemies() { enemies.clear(); }
    void clearMainCharacters() { mainCharacters.clear(); }
    void clearFriends() { friends.clear(); }
    void clearDrops() { drops.clear(); }
    void clearAnimatables() { animatables.clear(); }
    void clearProjectiles() { projectiles.clear(); }

    // Update all projectiles
    void updateProjectiles(float deltaTime) {
        for (auto& projectile : projectiles) {
            projectile.move(deltaTime);
        }
    }

    // Render the map
    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
        shader.use();

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniform3f(glGetUniformLocation(shader.getId(), "ambientColor"), ambientColor.x, ambientColor.y, ambientColor.z);

        terrainMesh.draw(shader);

        // Render enemies
        for (auto& enemy : enemies) {
            enemy.render(projectionMatrix, viewMatrix);
        }

        // Render main characters
        for (auto& mainChar : mainCharacters) {
            mainChar.render(projectionMatrix, viewMatrix);
        }

        // Render friends
        for (auto& friendChar : friends) {
            friendChar.render(projectionMatrix, viewMatrix);
        }

        // Render drops
        for (auto& drop : drops) {
            drop.render(projectionMatrix, viewMatrix);
        }

        // Render animatables
        for (auto& animatable : animatables) {
            animatable.render(projectionMatrix, viewMatrix);
        }

        // Render projectiles
        for (auto& projectile : projectiles) {
            projectile.render(projectionMatrix, viewMatrix);
        }
    }

    // Getters
    const std::vector<Enemy>& getEnemies() const { return enemies; }
    const std::vector<Main_Char>& getMainCharacters() const { return mainCharacters; }
    const std::vector<Friend>& getFriends() const { return friends; }
    const std::vector<Drop>& getDrops() const { return drops; }
    const std::vector<Animatable>& getAnimatables() const { return animatables; }
    const std::vector<Projectile>& getProjectiles() const { return projectiles; }
};
