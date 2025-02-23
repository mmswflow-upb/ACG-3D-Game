#pragma once
#include <string>
#include <vector>
#include "../../Resources/Model Packs/ProjectilePacks.h"

enum class CharacterPack {
    Main,
    Ice_Dyno,
    Fire_Dyno,
    Friend
};

struct CharacterModelAttributes {
    std::string modelPath;
    std::string texturePath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

/// Function to get character model attributes
inline CharacterModelAttributes getCharacterModelAttributes(CharacterPack pack) {
    switch (pack) {
    case CharacterPack::Main:
        return {
            "Resources/Models/Characters/main_char/main_char.obj",
            "Resources/Models/Characters/main_char/main_char.bmp", // Texture path
            "Shaders/Characters Shaders/mc/mc_vertex_shader.glsl",
            "Shaders/Characters Shaders/mc/mc_fragment_shader.glsl"
        };

    case CharacterPack::Ice_Dyno:
        return {
          "Resources/Models/Characters/ice_dyno/ice_dyno.obj",
            "Resources/Models/Characters/ice_dyno/ice_dyno.bmp", // Texture path
            "Shaders/Characters Shaders/enemy/enemy_vertex_shader.glsl",
            "Shaders/Characters Shaders/enemy/enemy_fragment_shader.glsl"
        };

    case CharacterPack::Fire_Dyno:
        return {
            "Resources/Models/Characters/lava_dyno/lavaDyno.obj",
            "Resources/Models/Characters/lava_dyno/lavaDyno.bmp", // Texture path
            "Shaders/Characters Shaders/enemy/mc_vertex_shader.glsl",
            "Shaders/Characters Shaders/enemy/mc_fragment_shader.glsl"
        };

    case CharacterPack::Friend:
        return {
            "Resources/Models/Characters/laylasaurus/laylasaurus.obj",
            "Resources/Models/Characters/laylasaurus/laylasaurus.bmp", // Texture path
            "Shaders/Characters Shaders/friend/friend_vertex_shader.glsl",
            "Shaders/Characters Shaders/friend/friend_fragment_shader.glsl"
        };

    default:
        return { "", "", "", "" };
    }
}

enum class MovementType {
    Straight,
    Circular,
    Free
};

struct CharacterGameAttributes {
    float health;
    float speed;
    std::vector<ProjectileType> vulnerableTo;
    glm::vec3 movementAxis;     // Axis for straight movement
    MovementType movementType;  // Movement type (Straight or Circular)
    glm::vec3 startingPosition; // Starting position
    float radius;               // Radius or limit for movement
    float scale;                // Scale of the model
    float fireRate;             // Fire rate
    float range;                // Shooting range
};


/// Function to set character game attributes
inline void getCharacterGameAttributes(CharacterPack pack,
    float& health,
    float& speed,
    std::vector<ProjectileType>& vulnerableTo,
    glm::vec3& movementAxis,
    MovementType& movementType,
    glm::vec3& startingPosition,
    float& radius,
    float& scale,
    float& fireRate,
    float& range) {
    switch (pack) {
    case CharacterPack::Main:
        health = 100.0f;
        speed = 5.0f;
        vulnerableTo = { ProjectileType::Fireball, ProjectileType::Iceball };
        movementAxis = glm::vec3(0.0f); // No movement axis
        movementType = MovementType::Free;
        startingPosition = glm::vec3(0.0,10.0f,0.0f);
        radius = 0.0f; // No radius
        scale = 1.0f; // Default scale
        fireRate = 0.0f;
        range = 0.0f;
        break;

    case CharacterPack::Ice_Dyno:
        health = 150.0f;
        speed = 3.5f;
        vulnerableTo = { ProjectileType::Bullet, ProjectileType::LaylasaurusFireball };
        movementAxis = glm::vec3(1.0f, 0.0f, 0.0f); // Moves along X-axis
        movementType = MovementType::Straight;
        startingPosition = glm::vec3(-5.0f, 0.0f, -5.0f); // Example starting position
        radius = 10.0f; // Radius for circular movement
        scale = 5.0f; // Slightly larger model
        fireRate = 1.0f; // 1 projectile per second
        range = 50.0f;
        break;

    case CharacterPack::Fire_Dyno:
        health = 200.0f;
        speed = 4.0f;
        vulnerableTo = { ProjectileType::Bullet, ProjectileType::LaylasaurusFireball };
        movementAxis = glm::vec3(0.0f, 0.0f, 1.0f); // Moves along Z-axis
        movementType = MovementType::Straight;
        startingPosition = glm::vec3(0.0f, 0.0f, -10.0f); // Example starting position
        radius = 25.0f; // Limit for straight movement
        scale = 5.0f; // Default scale
        fireRate = 0.5f; // 1 projectile every 2 seconds
        range = 50.0f;

        break;

    case CharacterPack::Friend:
        health = 100.0f;
        speed = 5.0f;
        vulnerableTo = { ProjectileType::Fireball, ProjectileType::Iceball };
        movementAxis = glm::vec3(0.0f); // No movement axis
        movementType = MovementType::Free;
        startingPosition = glm::vec3(0.0f);
        radius = 0.0f; // No radius
        scale = 1.0f; // Default scale
        fireRate = .5f;
        range = 50.0f;
        break;

    default:
        health = 0.0f;
        speed = 0.0f;
        vulnerableTo.clear();
        movementAxis = glm::vec3(0.0f);
        movementType = MovementType::Straight;
        startingPosition = glm::vec3(0.0f);
        radius = 0.0f;
        scale = 1.0f; // Default scale
        fireRate = 0.0f;
        range = 00.0f;

        break;
    }
}


