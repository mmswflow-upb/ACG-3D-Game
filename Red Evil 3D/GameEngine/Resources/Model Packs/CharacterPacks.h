#pragma once
#include <string>
#include <vector>
#include "../../Resources/Model Packs/ProjectilePacks.h"

enum class CharacterPack {
    Main,
    Ice_Dyno,
    Fire_Dyno,
    Earth_Dyno,
    Friend
};

struct CharacterModelAttributes {
    std::string modelPath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
    std::string texturePath;
};

/// Function to get character model attributes
inline CharacterModelAttributes getCharacterModelAttributes(CharacterPack pack) {
    switch (pack) {
    case CharacterPack::Main:
        return {
            "Resources/Models/Characters/main_char/main_char.obj",
            "Shaders/Characters Shaders/mc_normal_vertex_shader.glsl",
            "Shaders/Characters Shaders/mc_normal_fragment_shader.glsl",
            "Resources/Models/Characters/main_char/main_char.bmp" // Texture path
        };

    case CharacterPack::Ice_Dyno:
        return {
            "../Models/Characters/ice_dyno/ice_dyno.obj",
            "../../Shaders/Characters Shaders/ice_vertex.glsl",
            "../../Shaders/Characters Shaders/ice_fragment.glsl",
            "../Models/Characters/ice_dyno/ice_dyno.bmp" // Texture path
        };

    case CharacterPack::Fire_Dyno:
        return {
            "../Models/Characters/fire_dyno/fire_dyno.obj",
            "../../Shaders/Characters Shaders/fire_vertex.glsl",
            "../../Shaders/Characters Shaders/fire_fragment.glsl",
            "../Models/Characters/fire_dyno/fire_dyno.bmp" // Texture path
        };

    case CharacterPack::Earth_Dyno:
        return {
            "../Models/Characters/earth_dyno/earth_dyno.obj",
            "../../Shaders/Characters Shaders/earth_vertex.glsl",
            "../../Shaders/Characters Shaders/earth_fragment.glsl",
            "../Models/Characters/earth_dyno/earth_dyno.bmp" // Texture path
        };

    case CharacterPack::Friend:
        return {
            "../Models/Characters/friend/friend.obj",
            "../../Shaders/Characters Shaders/friend_vertex.glsl",
            "../../Shaders/Characters Shaders/friend_fragment.glsl",
            "../Models/Characters/friend/friend.bmp" // Texture path
        };

    default:
        return { "", "", "", "" };
    }
}

struct CharacterGameAttributes {
    float health;
    float speed;
    std::vector<ProjectileType> vulnerableTo;
};

/// Function to set character game attributes
inline void getCharacterGameAttributes(CharacterPack pack,
    float& health,
    float& speed,
    std::vector<ProjectileType>& vulnerableTo) {
    switch (pack) {
    case CharacterPack::Main:
        health = 100.0f;
        speed = 5.0f;
        vulnerableTo = { ProjectileType::Fireball, ProjectileType::IceShard };
        break;

    case CharacterPack::Ice_Dyno:
        health = 150.0f;
        speed = 3.5f;
        vulnerableTo = { ProjectileType::Bullet };
        break;

    case CharacterPack::Fire_Dyno:
        health = 120.0f;
        speed = 4.0f;
        vulnerableTo = { ProjectileType::Bullet };
        break;

    case CharacterPack::Earth_Dyno:
        health = 200.0f;
        speed = 2.5f;
        vulnerableTo = { ProjectileType::IceShard };
        break;

    case CharacterPack::Friend:
        health = 100.0f;
        speed = 4.0f;
        vulnerableTo = { ProjectileType::Fireball, ProjectileType::IceShard };
        break;

    default:
        health = 0.0f;
        speed = 0.0f;
        vulnerableTo.clear();
        break;
    }
}
