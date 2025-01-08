#pragma once
#include "../../Model Loading/mesh.h"
#include "../../Shaders/shader.h"
#include "../../Resources/Model Packs/DropPacks.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Drop {
private:
    Mesh mesh;
    Shader shader;
    glm::vec3 position;
    int amount; // The amount this drop provides

public:
    Drop(const Mesh& loadedMesh, const Shader& loadedShader, DropType type)
        : mesh(loadedMesh), shader(loadedShader) {

        // Get game-related attributes
        getDropGameAttributes(type, amount);

        // Initialize position
        position = glm::vec3(0.0f);
    }

    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
        shader.use();

        // Set the model matrix for the drop
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);

        // Calculate MVP matrix
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

        // Pass the MVP matrix to the shader
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);

        // Draw the mesh
        mesh.draw(shader);
    }

    const glm::vec3& getPosition() const { return position; }
    void setPosition(const glm::vec3& pos) { position = pos; }
    int getAmount() const { return amount; } // Getter for the amount
};
