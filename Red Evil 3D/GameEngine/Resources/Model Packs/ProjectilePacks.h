#pragma once
#include <string>

/// Enum class for Projectile Types
enum class ProjectileType {
    Bullet,
    Fireball,
    IceShard,
};

/// Struct for Projectile Model Attributes
struct ProjectileModelAttributes {
    std::string texturePath;
    std::string modelPath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

/// Struct for Projectile Game Attributes
struct ProjectileGameAttributes {
    float damage;  // Damage dealt by the projectile
    float speed;   // Speed of the projectile
};

/// Function to get Projectile Model Attributes
inline ProjectileModelAttributes getProjectileModelAttributes(ProjectileType type) {
    switch (type) {
    case ProjectileType::Bullet:
        return {
            "../Textures/Projectiles/bullet.png",
            "../Models/Tools/cube.obj",
            "../../Shaders/Projectiles Shaders/projectile_vertex.glsl",
            "../../Shaders/Projectiles Shaders/projectile_fragment.glsl"
        };
    case ProjectileType::Fireball:
        return {
            "../Textures/Projectiles/fireball.png",
            "../Models/Projectiles/fireball.obj",
            "../../Shaders/Projectiles Shaders/fireball_vertex.glsl",
            "../../Shaders/Projectiles Shaders/fireball_fragment.glsl"
        };
    case ProjectileType::IceShard:
        return {
            "../Textures/Projectiles/iceshard.png",
            "../Models/Projectiles/iceshard.obj",
            "../../Shaders/Projectiles Shaders/iceshard_vertex.glsl",
            "../../Shaders/Projectiles Shaders/iceshard_fragment.glsl"
        };
    default:
        return { "", "", "", "" };
    }
}

/// Function to get Projectile Game Attributes (modifies arguments by reference)
inline void getProjectileGameAttributes(ProjectileType type, float& damage, float& speed) {
    switch (type) {
    case ProjectileType::Bullet:
        damage = 25.0f;
        speed = 50.0f;
        break;
    case ProjectileType::Fireball:
        damage = 50.0f;
        speed = 30.0f;
        break;
    case ProjectileType::IceShard:
        damage = 40.0f;
        speed = 35.0f;
        break;
    default:
        damage = 0.0f;
        speed = 0.0f;
        break;
    }
}
