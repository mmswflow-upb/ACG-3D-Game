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
    std::string texturePath;
    std::string modelPath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

/// Struct for Drop Game Attributes
struct DropGameAttributes {
    int amount; // Amount of resource (e.g., health points, ammo count)
};

/// Function to get Drop Model Attributes (shaders, paths, etc.)
inline DropModelAttributes getDropModelAttributes(DropType type) {
    switch (type) {
    case DropType::HealthPack:
        return {
            "Resources/Textures/Drops/healthpack.png",
            "Resources/Models/Drops/healthpack.obj",
            "Shaders/Drop Shaders/healthpack_vertex_shader.glsl",
            "Shaders/Drop Shaders/healthpack_fragment_shader.glsl"
        };
    case DropType::Ammo_30:
        return {
            "Resources/Textures/Drops/ammo.png",
            "Resources/Models/Drops/ammo.obj",
            "Shaders/Drop Shaders/ammo_vertex_shader.glsl",
            "Shaders/Drop Shaders/ammo_fragment_shader.glsl"
        };
    case DropType::Ammo_60:
        return {
            "Resources/Textures/Drops/ammo.png",
            "Resources/Models/Drops/ammo.obj",
            "Shaders/Drop Shaders/ammo_vertex_shader.glsl",
            "Shaders/Drop Shaders/ammo_fragment_shader.glsl"
        };
    case DropType::Antidote_Vial:
        return {
            "Resources/Textures/Drops/antidote.png",
            "Resources/Models/Drops/antidote.obj",
            "Shaders/Drop Shaders/antidote_vertex_shader.glsl",
            "Shaders/Drop Shaders/antidote_fragment_shader.glsl"
        };
    default:
        return { "", "", "", "" };
    }
}

/// Function to get Drop Game Attributes (modifies arguments by reference)
inline void getDropGameAttributes(DropType type, int& amount) {
    switch (type) {
    case DropType::HealthPack:
        amount = 50;
        break;

    case DropType::Ammo_30:
        amount = 30;
        break;
    case DropType::Ammo_60:
        amount = 60;
        break;
    case DropType::Antidote_Vial:
        amount = 1;
        break;
    default:
        amount = 0;
        break;
    }
}