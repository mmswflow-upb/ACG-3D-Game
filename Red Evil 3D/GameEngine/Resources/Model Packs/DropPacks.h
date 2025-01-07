#pragma once
#include <string>

enum class DropType {
    HealthPack,
    Ammo_30,
    Ammo_60,
    Antidote_Vial
};

struct DropAttributes {
    std::string texturePath;
    std::string modelPath;
    int amount;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

inline DropAttributes getDropAttributes(DropType type) {
    switch (type) {
    case DropType::HealthPack:
        return { "", "", 50, // Placeholder paths
                 "", "" };

    case DropType::Ammo_30:
        return { "", "", 30, // Placeholder paths
                 "", "" };

    case DropType::Ammo_60:
        return { "", "", 60, // Placeholder paths
                 "", "" };

    case DropType::Antidote_Vial:
        return { "", "", 1, // Placeholder paths
                 "", "" };

    default:
        return { "", "", 0, "", "" };
    }
}
