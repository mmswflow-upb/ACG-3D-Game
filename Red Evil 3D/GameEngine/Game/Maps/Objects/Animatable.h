#pragma once
#include "../../../Model Loading/mesh.h"
#include "../../../Shaders/shader.h"
#include "../../../Resources/Model Packs/AnimatablePacks.h"
#include <gtc/matrix_transform.hpp>

class Animatable {
private:
    Mesh mesh;
    Shader shader;
    glm::vec3 position;
    glm::vec3 offset;
    float scale;
    bool visible;
    float timeElapsed; // Animation timer

public:
    Animatable(const Mesh& loadedMesh, const Shader& loadedShader, AnimatableType type)
        : mesh(loadedMesh), shader(loadedShader), position(0.0f), visible(true), timeElapsed(0.0f) {

        // Get game-related attributes
        getAnimatableGameAttributes(type, scale, offset);

        // Apply offset to initial position
        position += offset;
    }

    void setPosition(const glm::vec3& pos) { position = pos; }
    const glm::vec3& getPosition() const { return position; }

    void setVisible(bool isVisible) { visible = isVisible; }
    bool isVisible() const { return visible; }

    void update(float deltaTime) {
        if (!visible) return; // Skip updating if not visible
        timeElapsed += deltaTime; // Increment animation timer
    }

    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix, glm::vec3 lightColor, glm::vec3 lightPos, Camera& camera, double time) {
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
};
