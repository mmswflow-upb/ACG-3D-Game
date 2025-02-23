#pragma once
#include <string>

/// Enum class for Projectile Types
enum class ProjectileType {
    None,       // Represents no projectile
    Bullet,
    Fireball,
    Iceball,
	LaylasaurusFireball
};

/// Struct for Projectile Model Attributes
struct ProjectileModelAttributes {
    std::string modelPath;
    std::string texturePath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

/// Struct for Projectile Game Attributes
struct ProjectileGameAttributes {
    float damage;  // Damage dealt by the projectile
    float speed;   // Speed of the projectile
    float scale; // Scale of the projectile
    float maxDistance; //Max distance covered by projectile 
    std::string name;
};

/// Function to get Projectile Model Attributes
inline ProjectileModelAttributes getProjectileModelAttributes(ProjectileType type) {
    switch (type) {
    case ProjectileType::Bullet:
        return {
           "Resources/Models/Projectiles/Bullet/bullet.obj",
            "",
            "Shaders/Projectiles Shaders/Bullet Shaders/bullet_vertex_shader.glsl",
            "Shaders/Projectiles Shaders/Bullet Shaders/bullet_fragment_shader.glsl"
        };
    case ProjectileType::Fireball:
        return {
            "Resources/Models/Projectiles/Fireball/fireball.obj",
            "",
            "Shaders/Projectiles Shaders/Fireball Shaders/fireball_vertex_shader.glsl",
            "Shaders/Projectiles Shaders/Fireball Shaders/fireball_fragment_shader.glsl"
        };
    case ProjectileType::Iceball:
        return {
            "Resources/Models/Projectiles/Iceball/iceball.obj",
            "",
            "Shaders/Projectiles Shaders/Iceball Shaders/iceball_vertex_shader.glsl",
            "Shaders/Projectiles Shaders/Iceball Shaders/iceball_fragment_shader.glsl"
        };
    case ProjectileType::LaylasaurusFireball:
        return {
            "Resources/Models/Projectiles/Fireball/fireball.obj",
            "",
            "Shaders/Projectiles Shaders/Laylasaurus Fireball Shaders/laylasaurus_fireball_vertex_shader.glsl",
            "Shaders/Projectiles Shaders/Laylasaurus Fireball Shaders/laylasaurus_fireball_fragment_shader.glsl"
        };
    case ProjectileType::None:
    default:
        return { "", "", "", "" }; // Empty values for None or unrecognized types
    }
}

/// Function to get Projectile Game Attributes (modifies arguments by reference)
inline void getProjectileGameAttributes(ProjectileType type, float& damage, float& speed, float& scale, float& maxDistance, std::string& name) {
    switch (type) {
    case ProjectileType::Bullet:
        damage = 25.0f;
        speed = 10.0f;
        scale = 2.0f;
        maxDistance=50.0f;
		name="Bullet";
        break;
    case ProjectileType::Fireball:
        damage = 50.0f;
        speed = 15.0f;
        scale = 2.5f;
        maxDistance=60.0f;
		"Fireball";
        break;
    case ProjectileType::Iceball:
        damage = 40.0f;
        speed = 10.0f;
        scale = 0.05f;
        maxDistance = 50.0f;
		name= "Iceball";
        break;
	case ProjectileType::LaylasaurusFireball:
		damage = 40.0f;
		speed = 10.0f;
		scale = 0.05f;
		maxDistance = 50.0f;
        break;
    case ProjectileType::None:
    default:
        damage = 0.0f;
        speed = 0.0f; // No damage or speed for None type
        scale = 2.0f;
        maxDistance=50.0f;
		name="";
        break;
    }
}
