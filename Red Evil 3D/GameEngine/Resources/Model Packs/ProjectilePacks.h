#pragma once
#include <string>

enum class ProjectileType {
    Bullet,
    Fireball,
    IceShard,
};

struct ProjectileAttributes {
    float damage;
    float speed;
    std::string texturePath;
    std::string modelPath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

inline ProjectileAttributes getProjectileAttributes(ProjectileType type) {
    switch (type) {
    case ProjectileType::Bullet:
        return { 25.0f, 50.0f,
                 "", "../Models/Tools/cube.obj",
                 "../../Shaders/Projectiles Shaders/projectile_vertex.glsl", "../../Shaders/Projectiles Shaders/projectile_fragment.glsl" };

    case ProjectileType::Fireball:
        return { 50.0f, 30.0f,
                 "", "", // Placeholder paths
                 "", "" };

    case ProjectileType::IceShard:
        return { 40.0f, 35.0f,
                 "", "", // Placeholder paths
                 "", "" };

    default:
        return { 0.0f, 0.0f, "", "", "", "" };
    }
}
