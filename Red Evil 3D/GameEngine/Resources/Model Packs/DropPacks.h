#pragma once
#include <string>

/// Enum class for Drop Types
enum class DropType {
    HealthPack,
    Ammo_30,
    Ammo_60,
    Antidote_Vial
};

/// Struct for Drop Model Attributes
struct DropModelAttributes {
    std::string modelPath;
    std::string texturePath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

/// Struct for Drop Game Attributes
struct DropGameAttributes {
    std::string name;
    int amount; // Amount of resource (e.g., health points, ammo count)
};

/// Function to get Drop Model Attributes (shaders, paths, etc.)
inline DropModelAttributes getDropModelAttributes(DropType type) {
    switch (type) {
    case DropType::HealthPack:
        return {
            "Resources/Models/Drops/medkit/medkit.obj",
            "",
            "Shaders/Drops Shaders/medkit/medkit_vertex_shader.glsl",
            "Shaders/Drops Shaders/medkit/medkit_fragment_shader.glsl"
        };
    case DropType::Ammo_30:
        return {
            "Resources/Models/Drops/ammo30/ammo30.obj",
            "",
            "Shaders/Drops Shaders/ammo30/ammo30_vertex_shader.glsl",
            "Shaders/Drops Shaders/ammo30/ammo30_fragment_shader.glsl"
        };
    case DropType::Ammo_60:
        return {
            "Resources/Models/Drops/ammo60/ammo60.obj",
            "",
            "Shaders/Drops Shaders/ammo60/ammo60_vertex_shader.glsl",
            "Shaders/Drops Shaders/ammo60/ammo60_fragment_shader.glsl"
        };
    case DropType::Antidote_Vial:
        return {
            "Resources/Models/Drops/cure/antidote.obj",
            "Resources/Models/Drops/cure/antidote.bmp",
            "Shaders/Drops Shaders/antidote/antidote_vertex_shader.glsl",
            "Shaders/Drops Shaders/antidote/antidote_fragment_shader.glsl"
        };
    default:
        return { "", "", "", "" };
    }
}

/// Function to get Drop Game Attributes (modifies arguments by reference)
inline void getDropGameAttributes(DropType type, std::string& name,int& amount, float& scale, glm::vec3& position) {
    switch (type) {
    case DropType::HealthPack:
        name = "Medkit";
        amount = 50;
        scale = 0.5f; // Smaller size for health packs
        position = glm::vec3(0.0f, 0.0f, 0.0f); // Default starting position
        break;

    case DropType::Ammo_30:
        name = "Ammo-30";
        amount = 30;
        scale = 0.04f; // Medium size
        position = glm::vec3(20.0f, 8.0f, -20.0f); // Default starting position
        break;

    case DropType::Ammo_60:
        name = "Ammo-60";
        amount = 60;
        scale = 0.04f; // Slightly larger size
        position = glm::vec3(20.0f, 8.0f, -20.0f); // Default starting position

        break;

    case DropType::Antidote_Vial:
        name = "Antidote";
        amount = 1;
        scale = 0.3f; // Smaller size for a vial
        position = glm::vec3(20.0f, 8.0f, -20.0f); // Default starting position

        break;

    default:
        name = "None";
        amount = 0;
        scale = 1.0f; // Default scale
        position = glm::vec3(0.0f, 0.0f, 0.0f); // Default starting position
        break;
    }
}
