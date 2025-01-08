#pragma once
#include <string>

/// Enum class for Gun Packs
enum class GunPack {
    Pistol,
    Rifle,
    Shotgun,
    Sniper
};

/// Struct for Gun Model Attributes
struct GunModelAttributes {
    std::string texturePath;
    std::string modelPath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

/// Function to get Gun Model Attributes
inline GunModelAttributes getGunModelAttributes(GunPack pack) {
    switch (pack) {
    case GunPack::Pistol:
        return {
            "Resources/Textures/Guns/pistol.png",
            "Resources/Models/Guns/pistol.obj",
            "Shaders/Gun Shaders/pistol_vertex_shader.glsl",
            "Shaders/Gun Shaders/pistol_fragment_shader.glsl"
        };
    case GunPack::Rifle:
        return {
            "Resources/Textures/Guns/rifle.png",
            "Resources/Models/Guns/rifle.obj",
            "Shaders/Gun Shaders/rifle_vertex_shader.glsl",
            "Shaders/Gun Shaders/rifle_fragment_shader.glsl"
        };
    case GunPack::Shotgun:
        return {
            "Resources/Textures/Guns/shotgun.png",
            "Resources/Models/Guns/shotgun.obj",
            "Shaders/Gun Shaders/shotgun_vertex_shader.glsl",
            "Shaders/Gun Shaders/shotgun_fragment_shader.glsl"
        };
    case GunPack::Sniper:
        return {
            "Resources/Textures/Guns/sniper.png",
            "Resources/Models/Guns/sniper.obj",
            "Shaders/Gun Shaders/sniper_vertex_shader.glsl",
            "Shaders/Gun Shaders/sniper_fragment_shader.glsl"
        };
    default:
        return { "", "", "", "" };
    }
}

/// Function to get Gun Game Attributes (modifies arguments by reference)
inline void getGunGameAttributes(
    GunPack pack,
    float& damage,
    float& fireRate,
    int& magazineSize,
    float& reloadTime,
    float& range
) {
    switch (pack) {
    case GunPack::Pistol:
        damage = 25.0f;
        fireRate = 2.0f;
        magazineSize = 12;
        reloadTime = 1.5f;
        range = 20.0f;
        break;
    case GunPack::Rifle:
        damage = 35.0f;
        fireRate = 5.0f;
        magazineSize = 30;
        reloadTime = 2.5f;
        range = 50.0f;
        break;
    case GunPack::Shotgun:
        damage = 80.0f;
        fireRate = 1.0f;
        magazineSize = 8;
        reloadTime = 3.0f;
        range = 15.0f;
        break;
    case GunPack::Sniper:
        damage = 150.0f;
        fireRate = 0.5f;
        magazineSize = 5;
        reloadTime = 3.5f;
        range = 100.0f;
        break;
    default:
        damage = 0.0f;
        fireRate = 0.0f;
        magazineSize = 0;
        reloadTime = 0.0f;
        range = 0.0f;
        break;
    }
}
