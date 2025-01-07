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
};

inline DropAttributes getDropAttributes(DropType type) {
    switch (type) {
    case DropType::HealthPack:
        return { "assets/drops/HealthPack.png", "assets/models/HealthPack.obj", 50 };

    case DropType::Ammo_30:
        return { "assets/drops/Ammo.png", "assets/models/Ammo.obj", 30 };

    case DropType::Ammo_60:
        return { "assets/drops/Ammo.png", "assets/models/Ammo.obj", 60 };

    case DropType::Antidote_Vial:
        return { "assets/drops/AntidoteVial.png", "assets/models/AntidoteVial.obj", 1 };

    default:
        return { "", "", 0 };
    }
}
