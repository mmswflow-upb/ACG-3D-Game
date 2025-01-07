#pragma once
#include <string>
#include <vector>
#include "../../../Model Loading/texture.h"
#include "../../../Model Loading/meshLoaderObj.h"
#include "../../../Model Loading/mesh.h"
#include "../../../Shaders/shader.h"
#include "../../../Camera/camera.h"
#include "../../../Graphics/window.h"

class Enemy {
private:
    Mesh mesh;           // The 3D model mesh
    Shader shader;       // Shader used for rendering
    glm::vec3 position;  // Position of the enemy
    float speed;         // Movement speed

    // Private load function that supports textures or no textures
    void load(const std::string& modelPath, const std::vector<Texture>& textures = {}) {
        MeshLoaderObj loader;

        // Use the appropriate overload of loadObj()
        if (textures.empty()) {
            mesh = loader.loadObj(modelPath); // No textures provided
        }
        else {
            mesh = loader.loadObj(modelPath, textures); // Textures provided
        }
    }

public:
    // Constructor with textures
    Enemy(const std::string& modelPath, const std::vector<Texture>& textures,
        const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
        : shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str()), // Convert to const char*
        position(0.0f), speed(10.0f) {
        load(modelPath, textures);
    }

    // Constructor without textures
    Enemy(const std::string& modelPath,
        const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
        : shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str()), // Convert to const char*
        position(0.0f), speed(10.0f) {
        load(modelPath);
    }

    // Update enemy position
    void update(float deltaTime) {
        position.x += speed * deltaTime; // Example movement logic
    }
   
    void render(const Camera& camera, const Window& window) {
        shader.use();

        glm::mat4 projectionMatrix = glm::perspective(90.0f, window.getWidth() * 1.0f / window.getHeight(), 0.1f, 1000.0f);
        glm::mat4 viewMatrix = glm::lookAt(camera.getCameraPosition(), camera.getCameraPosition() + camera.getCameraViewDirection(), camera.getCameraUp());
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);

        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);

        mesh.draw(shader);
    }

};
