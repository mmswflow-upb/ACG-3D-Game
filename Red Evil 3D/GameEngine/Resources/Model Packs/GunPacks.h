#pragma once
#include <string>

/// Enum class for Gun Packs
enum class GunPack {
    Pistol
};

/// Struct for Gun Model Attributes
struct GunModelAttributes {
    std::string modelPath;
    std::string texturePath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

/// Function to get Gun Model Attributes
inline GunModelAttributes getGunModelAttributes(GunPack pack) {
    switch (pack) {
    case GunPack::Pistol:
        return {
            "Resources/Models/Tools/LowPolyPistol/lowPolyGun.obj",
            "Resources/Models/Tools/LowPolyPistol/lowPolyGun.bmp",
            "Shaders/GunsShaders/Pistol/pistol_vertex_shader.glsl",
            "Shaders/GunsShaders/Pistol/pistol_fragment_shader.glsl"
        };
    
    default:
        return { "", "", "", "" };
    }
}

/// Function to get Gun Game Attributes (modifies arguments by reference)
inline void getGunGameAttributes(
    GunPack pack,
    std::string& name,
    float& damage,
    float& fireRate,
    int& magazineSize,
    float& reloadTime,
    float& range,
    float scale,
    glm::vec3& position
) {
    switch (pack) {
    case GunPack::Pistol:
        name = "Pistol";
        damage = 25.0f;
        fireRate = 2.0f;
        magazineSize = 12;
        reloadTime = 1.5f;
        range = 20.0f;
        scale = 5.0f;
        position = glm::vec3(0.0f, 40.0f, 0.0f); // Default position
        break;
    
    default:
        name = "None";
        damage = 0.0f;
        fireRate = 0.0f;
        magazineSize = 0;
        reloadTime = 0.0f;
        range = 0.0f;
        scale = 1.0f, // Default scale
        position = glm::vec3(0.0f, 0.0f, 0.0f); // Default position
        break;
    }
}
