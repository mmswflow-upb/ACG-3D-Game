#pragma once
#include "../../Model Loading/mesh.h"
#include "../../Shaders/shader.h"
#include "../../Resources/Model Packs/CelestialPacks.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Celestial {
private:
    Mesh mesh;
    Shader shader;
    glm::vec3 currentPosition; // Current position
    glm::vec3 color;           // Color of the celestial object
    float scale;               // Scale factor
    bool visible;
    float orbitRadius;         // Orbit radius from the pack
    float orbitSpeed;          // Orbit speed from the pack
    float currentAngle;        // Current angle for orbit calculation
    CelestialPack pack;

public:
    Celestial(const Mesh& loadedMesh, const Shader& loadedShader, CelestialPack pack)
        : mesh(loadedMesh), shader(loadedShader), visible(true), currentAngle(0.0f), pack(pack) {

        // Get in-game attributes
        glm::vec3 startingPosition;
        getCelestialGameAttributes(pack, startingPosition, color, scale, orbitRadius, orbitSpeed);
        currentPosition = startingPosition; // Set initial position
    }

    void setPosition(const glm::vec3& pos) { currentPosition = pos; }
    const glm::vec3& getPosition() const { return currentPosition; }
    
    
    void move(float deltaTime, float sunAngle = 0.0f) {
        constexpr float TWO_PI_DEG = 360.0f; // Full rotation in degrees

        if (pack == CelestialPack::Moon) {
            // Moon lags behind the sun by 45 degrees
            currentAngle = sunAngle - 180.0f;
            if (currentAngle < 0.0f) {
                currentAngle += TWO_PI_DEG;
            }
        }
        else {
            // Increment the angle based on orbit speed
            currentAngle += orbitSpeed * deltaTime;
            if (currentAngle > TWO_PI_DEG) {
                currentAngle -= TWO_PI_DEG;
            }
        }

        // Calculate circular orbit using degrees
        currentPosition.x = orbitRadius * glm::cos(glm::radians(currentAngle)); // Convert to radians for glm::cos
        currentPosition.y = orbitRadius * glm::sin(glm::radians(currentAngle)); // Convert to radians for glm::sin

        // Z position remains constant (e.g., aligned with the origin)
        currentPosition.z = 0.0f;

        
    }

    float getAngle() {
        return currentAngle;
    }
    CelestialPack getPack() {
        return pack;
    }
    float getTime()  {
        // Return the normalized time (0.0 to 1.0) based on the current angle in the orbit
        if(pack == CelestialPack::Moon) std::cout << "MOON: " << currentAngle << "\n";
        if (pack == CelestialPack::Sun) std::cout << "SUN: " << currentAngle << "\n";
        return abs( currentAngle * 1.0f / (360.0f));
    }

    static void determineTimeAndSetLight(Celestial& sun, Celestial& moon, glm::vec3& lightColor, glm::vec3& lightPos, glm::vec4& skyColor) {
        const float horizonRange = 20.0f; // Range for smooth transition near the horizon

        // Define the base colors
        glm::vec3 dayLightColor = glm::vec3(1.0f, 0.9f, 0.7f); // Bright yellowish light
        glm::vec3 nightLightColor = glm::vec3(0.7f, 0.7f, 1.0f); // Soft bluish light

        glm::vec4 daySkyColor = glm::vec4(0.53f, 0.81f, 0.92f, 1.0f); // Light blue (daytime)
        glm::vec4 nightSkyColor = glm::vec4(0.02f, 0.02f, 0.1f, 1.0f); // Black (nighttime)

        // Get the Y positions of the sun and moon
        float sunY = sun.getPosition().y;
        float moonY = moon.getPosition().y;

        // Determine if it's day or night
        bool isDay = sunY > 0; // Daytime when the sun is above the horizon

        // Smooth transition factor based on the sun's position near the horizon
        float transitionFactor = glm::clamp((sunY + horizonRange) / (2.0f * horizonRange), 0.0f, 1.0f);

        if (isDay) {
            // Daytime: Blend from horizon to full daylight
            lightColor = glm::mix(nightLightColor, dayLightColor, transitionFactor);
            skyColor = glm::mix(nightSkyColor, daySkyColor, transitionFactor);
            lightPos = sun.getPosition();
        }
        else {
            // Nighttime: Blend from horizon to full night
            transitionFactor = glm::clamp((moonY + horizonRange) / (2.0f * horizonRange), 0.0f, 1.0f);
            lightColor = glm::mix(dayLightColor, nightLightColor, transitionFactor);
            skyColor = glm::mix(daySkyColor, nightSkyColor, transitionFactor);
            lightPos = moon.getPosition();
        }
    }



    void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
        if (!visible) return;
        shader.use();
        glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0), glm::vec3(scale));
        modelMatrix = glm::translate(modelMatrix, currentPosition);
        glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

        float angleRadians = glm::radians(currentAngle) ;
        glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniform1fv(glGetUniformLocation(shader.getId(), "angle"), 1, &angleRadians );

        mesh.draw(shader);

    }
};
