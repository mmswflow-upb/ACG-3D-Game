#pragma once
#include "../../../Model Loading/mesh.h"
#include "../../../Shaders/shader.h"
#include "../../../Resources/Model Packs/AnimatablePacks.h"
#include "../../../Camera/camera.h" // Ensure the Camera class is available
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// The AnimatableType enum should be defined in AnimatablePacks.h
// For example:
// enum class AnimatableType { Tree_Normal, Tree_Burnt, ... };

class Animatable {
private:
    Mesh mesh;
    Shader shader;
    glm::vec3 position;
    glm::vec3 offset;       // An extra offset if needed (fetched from attributes)
    float scale;
    bool visible;
    float timeElapsed;      // Timer used for animation (if needed)

public:
    // Constructor: similar to the character constructor, retrieve game attributes based on AnimatableType.
    Animatable(const Mesh& loadedMesh, const Shader& loadedShader, AnimatableType type)
        : mesh(loadedMesh), shader(loadedShader), position(0.0f), visible(true), timeElapsed(0.0f)
    {
        // Retrieve game-related attributes for this animatable object.
        // This function should fill in scale and offset (and other parameters if needed)
        getAnimatableGameAttributes(type, scale, offset);

        // Set the initial position by applying the offset.
        position += offset;
    }

    // Setters and Getters for Position and Visibility
    void setPosition(const glm::vec3& pos) { position = pos; }
    const glm::vec3& getPosition() const { return position; }

    void setVisible(bool isVisible) { visible = isVisible; }
    bool isVisible() const { return visible; }

    // Update function: Increases the time elapsed; you can extend this for more complex animation.
    void update(float deltaTime) {
        if (!visible) return;
        timeElapsed += deltaTime;
    }

    // Render function: Similar to the main character render, but includes the time value.
    // Note that we pass the Camera by reference so that its position can be accessed.
    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix,
        glm::vec3 lightColor, glm::vec3 lightPos, Camera* camera, double time, bool* animating)
    {
        if (!animating) return;

		if ((*animating) == false) timeElapsed = 0.0f;

        shader.use();

        // Build the model transformation matrix.
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));

        // Calculate the final MVP matrix.
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

        // Set shader uniforms. Ensure your shader has uniforms: "MVP", "lightColor", "lightPos", "viewPos", and optionally time-based uniforms.
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniform3fv(glGetUniformLocation(shader.getId(), "lightColor"), 1, glm::value_ptr(lightColor));
        glUniform3fv(glGetUniformLocation(shader.getId(), "lightPos"), 1, glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(shader.getId(), "viewPos"), 1, glm::value_ptr(camera->getCameraPosition()));

        // Optionally, if your shader supports time-based animation, pass the current time.
        glUniform1f(glGetUniformLocation(shader.getId(), "time"), static_cast<float>(time));

        // Draw the mesh.
        mesh.draw(shader);
    }
};
