#pragma once
#include "../../Model Loading/mesh.h"
#include "../../Shaders/shader.h"
#include "../../Camera/camera.h"
#include "../../Resources/Model Packs/DropPacks.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Drop {
private:
    Mesh mesh;
    std::string name;
    Shader shader;
    glm::vec3 position;
    float scale;      // Scaling factor
    int amount;       // The amount this drop provides
    float rotationAngle;
    DropType type;
    bool equipped;

public:
    Drop( Mesh& loadedMesh,  Shader& loadedShader, DropType type)
        : mesh(loadedMesh), shader(loadedShader), position(0.0f), rotationAngle(0.0f), type(type), name(""), equipped(false) {
        // Get game-related attributes
        getDropGameAttributes(type, name, amount, scale, position);
    }

    void render( glm::mat4 projectionMatrix,  glm::mat4 viewMatrix,  glm::vec3 lightColor, glm::vec3 lightPos,  Camera* camera) {
        shader.use();

        // Set the model matrix with scaling, position, and rotation
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
        modelMatrix = glm::rotate(modelMatrix, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scale)); // Apply scaling

        glm::mat4 MVP = (projectionMatrix) * (viewMatrix) * modelMatrix;

        // Pass the MVP matrix and other uniforms to the shader
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "model"), 1, GL_FALSE, &modelMatrix[0][0]);
        glUniform3fv(glGetUniformLocation(shader.getId(), "lightColor"), 1, glm::value_ptr(lightColor));
        glUniform3fv(glGetUniformLocation(shader.getId(), "lightPos"), 1, glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(shader.getId(), "viewPos"), 1, glm::value_ptr(camera->getCameraPosition()));

        mesh.draw(shader);
    }

     glm::vec3 getPosition()  { return position; }
    void setPosition( glm::vec3 pos) { position = pos; }
    DropType getType()  { return type; }
    float getScale()  { return scale; }
    int getAmount()  { return amount; }
     std::string getName()  { return name; }
    void setEquipped(bool newEquip) { equipped = newEquip; }
    bool isEquipped()  { return equipped; }
};
