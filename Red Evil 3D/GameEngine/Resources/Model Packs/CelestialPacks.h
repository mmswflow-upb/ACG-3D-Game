#pragma once
#include <string>
#include <glm.hpp>

/// Enum class for Celestial Packs
enum class CelestialPack {
    Sun,
    Moon
};

/// Struct for celestial model-related attributes
struct CelestialModelAttributes {
    std::string modelPath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
    std::string texturePath;
};

/// Function to get celestial model attributes
inline CelestialModelAttributes getCelestialModelAttributes(CelestialPack pack) {
    switch (pack) {
    case CelestialPack::Sun:
        return {
            "Resources/Models/Celestials/sun.obj",
            "Shaders/Celestial Shaders/sun_vertex_shader.glsl",
            "Shaders/Celestial Shaders/sun_fragment_shader.glsl",
            "" // No texture for the sun
        };
    case CelestialPack::Moon:
        return {
            "Resources/Models/Celestials/moon.obj",
            "Shaders/Celestial Shaders/moon_vertex_shader.glsl",
            "Shaders/Celestial Shaders/moon_fragment_shader.glsl",
            "" // No texture for the moon
        };
    default:
        return { "", "", "", "" };
    }
}

/// Function to get celestial game-related attributes
inline void getCelestialGameAttributes(
    CelestialPack pack,
    glm::vec3& startingPosition,
    glm::vec3& color,
    float& scale,
    float& orbitRadius,
    float& orbitSpeed
) {
    switch (pack) {
    case CelestialPack::Sun:
        startingPosition = glm::vec3(0.0f, 100.0f, -200.0f);
        color = glm::vec3(1.0f, 0.8f, 0.2f); // Bright yellow
        scale = 10.0f;                      // Large scale
        orbitRadius = 300.0f;               // Larger orbit radius
        orbitSpeed = 0.5f;                  // Slower orbit speed
        break;
    case CelestialPack::Moon:
        startingPosition = glm::vec3(-200.0f, 50.0f, 300.0f);
        color = glm::vec3(0.9f, 0.9f, 1.0f); // Soft white
        scale = 5.0f;                       // Medium scale
        orbitRadius = 150.0f;               // Smaller orbit radius
        orbitSpeed = 1.5f;                  // Faster orbit speed
        break;
    default:
        startingPosition = glm::vec3(0.0f);
        color = glm::vec3(1.0f);
        scale = 1.0f;         // Default scale
        orbitRadius = 100.0f; // Default orbit radius
        orbitSpeed = 1.0f;    // Default orbit speed
        break;
    }
}
