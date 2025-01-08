#pragma once
#include "../../Model Loading/mesh.h"
#include "../../Shaders/shader.h"
#include "../../Resources/Model Packs/AnimatablePacks.h"
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

    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
        if (!visible) return;

        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scale)); // Apply scaling
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

        shader.use();

        // Pass MVP matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);

        // Pass timeElapsed to the shader for animation
        glUniform1f(glGetUniformLocation(shader.getId(), "timeElapsed"), timeElapsed);

        // Render the mesh
        mesh.draw(shader);
    }
};
