#pragma once
#include <string>
#include <glm.hpp>

enum class CelestialPack {
    Sun,
    Moon
};

struct CelestialAttributes {
    std::string name;
    glm::vec3 color;
    float scale;
    std::string modelPath;
    glm::vec3 position;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
    std::string texturePath;
};

inline CelestialAttributes getCelestialAttributes(CelestialPack pack) {
    switch (pack) {
    case CelestialPack::Sun:
        return {
            "Sun",
            glm::vec3(1.0f, 0.8f, 0.2f),
            10.0f,
            "Resources/Models/Celestials/sun.obj",
            glm::vec3(0.0f, 100.0f, -200.0f),
            "Shaders/Celestial Shaders/sun_vertex_shader.glsl",
            "Shaders/Celestial Shaders/sun_fragment_shader.glsl"
            ""
        };

    default:
        return { "Unknown", glm::vec3(1.0f), 1.0f, "", glm::vec3(0.0f), "", "" , ""};
    }
}
