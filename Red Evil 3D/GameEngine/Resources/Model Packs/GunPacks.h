#pragma once
#include <string>

enum class GunPack {
    Pistol,
    Rifle,
    Shotgun,
    Sniper
};

struct GunAttributes {
    std::string name;
    float damage;
    float fireRate;
    int magazineSize;
    float reloadTime;
    float range;
    std::string texturePath;
    std::string modelPath;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

inline GunAttributes getGunAttributes(GunPack pack) {
    switch (pack) {
    case GunPack::Pistol:
        return { "Pistol", 25.0f, 2.0f, 12, 1.5f, 20.0f,
                 "", "", // Placeholder paths
                 "", "" };

    case GunPack::Rifle:
        return { "Rifle", 35.0f, 5.0f, 30, 2.5f, 50.0f,
                 "", "", // Placeholder paths
                 "", "" };

    case GunPack::Shotgun:
        return { "Shotgun", 80.0f, 1.0f, 8, 3.0f, 15.0f,
                 "", "", // Placeholder paths
                 "", "" };

    case GunPack::Sniper:
        return { "Sniper", 150.0f, 0.5f, 5, 3.5f, 100.0f,
                 "", "", // Placeholder paths
                 "", "" };

    default:
        return { "Unknown", 0.0f, 0.0f, 0, 0.0f, 0.0f, "", "", "", "" };
    }
}
