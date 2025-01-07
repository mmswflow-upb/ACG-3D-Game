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
};

inline ProjectileAttributes getProjectileAttributes(ProjectileType type) {
    switch (type) {
    case ProjectileType::Bullet:
        return { 25.0f, 50.0f, "assets/projectiles/Bullet.png", "assets/models/Bullet.obj" };

    case ProjectileType::Fireball:
        return { 50.0f, 30.0f, "assets/projectiles/Fireball.png", "assets/models/Fireball.obj" };

    case ProjectileType::IceShard:
        return { 40.0f, 35.0f, "assets/projectiles/IceShard.png", "assets/models/IceShard.obj" };

    default:
        return { 0.0f, 0.0f, "", "" };
    }
}

