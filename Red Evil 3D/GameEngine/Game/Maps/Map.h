#pragma once
#include <vector>
#include <string>
#include "../Entities/Enemies/Enemy.h"
#include "Objects/Drop.h"
#include "Objects/Animatable.h"
#include "../../Shaders/shader.h"
#include "../../Model Loading/mesh.h"
#include "../../Camera/camera.h"
#include "../../Graphics/window.h"

class Map {
private:
    std::vector<Enemy> enemies;
    std::vector<Drop> Drops;
    std::vector<Animatable> animatables;

    Shader mapShader;
    Mesh terrain;

    void loadTerrain(const std::string& terrainPath, const std::string& vertexShader, const std::string& fragmentShader) {
        MeshLoaderObj loader;
        terrain = loader.loadObj(terrainPath);
        mapShader = Shader(vertexShader, fragmentShader);
    }

public:
    Map(const std::string& terrainPath, const std::string& vertexShader, const std::string& fragmentShader) {
        loadTerrain(terrainPath, vertexShader, fragmentShader);
    }

    void addEnemy(const std::string& modelPath, const std::string& texturePath) {
        enemies.emplace_back(modelPath, texturePath);
    }

    void addDrop(const std::string& modelPath, const std::string& texturePath) {
        Drops.emplace_back(modelPath, texturePath);
    }

    void addAnimatable(const std::string& modelPath, const std::string& vertexShader, const std::string& fragmentShader) {
        animatables.emplace_back(modelPath, vertexShader, fragmentShader);
    }

    void update(Window& window, float deltaTime) {
        if (!window.isPaused()) {
            for (auto& enemy : enemies) {
                enemy.update(deltaTime);
            }
        }
        for (auto& animatable : animatables) {
            animatable.update(deltaTime);
        }
    }

    void render(const Camera& camera, Window& window) {
        mapShader.use();
        glm::mat4 projectionMatrix = glm::perspective(90.0f, window.getWidth() * 1.0f / window.getHeight(), 0.1f, 1000.0f);
        glm::mat4 viewMatrix = glm::lookAt(camera.getCameraPosition(), camera.getCameraPosition() + camera.getCameraViewDirection(), camera.getCameraUp());
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
        glUniformMatrix4fv(glGetUniformLocation(mapShader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);

        terrain.draw(mapShader);

        for (auto& enemy : enemies) {
            enemy.render(camera, window);
        }
        for (auto& Drop : Drops) {
            Drop.render(camera, window);
        }
        for (auto& animatable : animatables) {
            animatable.render(camera, window);
        }
    }
};
